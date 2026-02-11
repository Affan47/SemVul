eng_font_draw(void *data, void *context, void *surface, Evas_Font_Set *font __UNUSED__, int x, int y, int w __UNUSED__, int h __UNUSED__, int ow __UNUSED__, int oh __UNUSED__, Evas_Text_Props *intl_props)
{
   Render_Engine *re;

   re = (Render_Engine *)data;
   eng_window_use(re->win);
   evas_gl_common_context_target_surface_set(re->win->gl_context, surface);
   re->win->gl_context->dc = context;
     {

        static RGBA_Image *im = NULL;

        if (!im)
          im = (RGBA_Image *)evas_cache_image_empty(evas_common_image_cache_get());
        im->cache_entry.w = re->win->gl_context->shared->w;
        im->cache_entry.h = re->win->gl_context->shared->h;

        evas_common_draw_context_font_ext_set(context,
                                              re->win->gl_context,
                                              evas_gl_font_texture_new,
                                              evas_gl_font_texture_free,
                                              evas_gl_font_texture_draw);
        evas_common_font_draw_prepare(intl_props);
        evas_common_font_draw(im, context, x, y, intl_props);
        evas_common_draw_context_font_ext_set(context,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL);
     }
}
