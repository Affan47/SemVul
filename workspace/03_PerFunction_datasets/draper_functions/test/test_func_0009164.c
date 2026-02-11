eng_gl_surface_create(void *data __UNUSED__, void *config, int w, int h)
{
#ifdef EVAS_GL
   Render_Engine_GL_Surface *sfc;
   Evas_GL_Config *cfg;

   sfc = calloc(1, sizeof(Render_Engine_GL_Surface));
   if (!sfc) return NULL;

   cfg = (Evas_GL_Config *)config;

   sfc->initialized  = 0;
   sfc->w            = w;
   sfc->h            = h;


   switch (cfg->color_format)
     {

      case EVAS_GL_RGB_888:
         sfc->internal_fmt = OSMESA_RGB;
         sfc->internal_cpp = 3;
         break;
      case EVAS_GL_RGBA_8888:
         sfc->internal_fmt = OSMESA_BGRA;
         sfc->internal_cpp = 4;
         break;
      default:
         sfc->internal_fmt = OSMESA_RGBA;
         sfc->internal_cpp = 4;
         break;
     }


   switch (cfg->depth_bits)
     {
      case EVAS_GL_DEPTH_BIT_8:
         sfc->depth_bits = 8;
         break;
      case EVAS_GL_DEPTH_BIT_16:
         sfc->depth_bits = 16;
         break;
      case EVAS_GL_DEPTH_BIT_24:
         sfc->depth_bits = 24;
         break;
      case EVAS_GL_DEPTH_BIT_32:
         sfc->depth_bits = 32;
         break;
      case EVAS_GL_DEPTH_NONE:
      default:
         sfc->depth_bits = 0;
         break;
     }


   switch (cfg->stencil_bits)
     {
      case EVAS_GL_STENCIL_BIT_1:
         sfc->stencil_bits = 1;
         break;
      case EVAS_GL_STENCIL_BIT_2:
         sfc->stencil_bits = 2;
         break;
      case EVAS_GL_STENCIL_BIT_4:
         sfc->stencil_bits = 4;
         break;
      case EVAS_GL_STENCIL_BIT_8:
         sfc->stencil_bits = 8;
         break;
      case EVAS_GL_STENCIL_BIT_16:
         sfc->stencil_bits = 16;
         break;
      case EVAS_GL_STENCIL_NONE:
      default:
         sfc->stencil_bits = 0;
         break;
     }

   sfc->buffer = malloc(sizeof(unsigned char)*sfc->internal_cpp*w*h);

   if (!sfc->buffer)
     {
        free(sfc);
        return NULL;
     }

   return sfc;
#else
   (void) config;
   (void) w;
   (void) h;
   return NULL;
#endif
}
