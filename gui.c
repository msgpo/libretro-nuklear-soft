/* nuklear - v1.00 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <libretro.h>
#include <gui.h>

extern retro_log_printf_t log_cb;

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION

#define NK_RETRO_SOFT_IMPLEMENTATION

#include "nuklear.h"
#include "nuklear_retro_soft.h"

static RSDL_Surface *screen_surface;
static nk_retro_Font *RSDL_font;

#define UNUSED(a) (void)a
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a)/sizeof(a)[0])

float bg[4];
struct nk_color background;
struct nk_context *ctx;

#if !defined(EXAMPLE_CANVAS) && !defined(NO_EXAMPLE)
#include "overview.c"
#endif

int gui_init()
{
#ifdef M16B
    screen_surface=Retro_CreateRGBSurface16(rwidth,rheight,16,0,0,0,0);
#else
    screen_surface=Retro_CreateRGBSurface32(rwidth,rheight,32,0,0,0,0);
#endif

    frame_buf=screen_surface->pixels;

    RSDL_font = (nk_retro_Font*)calloc(1, sizeof(nk_retro_Font));
    RSDL_font->width = 8; 
    RSDL_font->height = 8; 
    if (!RSDL_font)
        return -1;

    ctx = nk_retro_init(RSDL_font,screen_surface,rwidth,rheight);

#if !defined(EXAMPLE_CANVAS) && !defined(NO_EXAMPLE)
    background = nk_rgb(28,48,62);
#endif

   log_cb(RETRO_LOG_INFO, "Init nuklear %d\n",0);

   return 0;
}

int gui_free()
{
    free(RSDL_font);
    nk_retro_shutdown();
    Retro_FreeSurface(screen_surface);

   return 0;
}

int gui_event()
{
   int evt;

   nk_input_begin(ctx);
   nk_retro_handle_event(&evt,1);
   nk_input_end(ctx);

   return 0;
}

int gui_main()
{

#if !defined(EXAMPLE_CANVAS) && !defined(NO_EXAMPLE)
   overview(ctx);
#endif
   nk_retro_render(nk_rgb(30,30,30));

    return 0;
}

int gui_frame()
{
   gui_event();
   gui_main();

   return 0;
}

