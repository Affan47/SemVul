evas_gl_common_texture_native_new(Evas_Engine_GL_Context *gc, unsigned int w, unsigned int h, int alpha, Evas_GL_Image *im)
{
   Evas_GL_Texture *tex;

   tex = calloc(1, sizeof(Evas_GL_Texture));
   if (!tex) return NULL;

   tex->gc = gc;
   tex->references = 1;
   tex->alpha = alpha;
   if (alpha)
     {
        if (gc->shared->info.bgra)
          tex->pt = _pool_tex_native_new(gc, w, h, rgba_ifmt, rgba_fmt, im);
        else
          tex->pt = _pool_tex_native_new(gc, w, h, rgba_ifmt, rgba_fmt, im);
     }
   else
     {
        if (gc->shared->info.bgra)
          tex->pt = _pool_tex_native_new(gc, w, h, rgb_ifmt, rgb_fmt, im);
        else
          tex->pt = _pool_tex_native_new(gc, w, h, rgb_ifmt, rgb_fmt, im);
     }
   if (!tex->pt)
     {
        free(tex);
        return NULL;
     }
   tex->x = 0;
   tex->y = 0;
   tex->w = w;
   tex->h = h;
   tex->pt->references++;
   return tex;
}
