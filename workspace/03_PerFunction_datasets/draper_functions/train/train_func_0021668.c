eng_image_alpha_set(void *data, void *image, int has_alpha)
{
   Render_Engine *re;
   Evas_GL_Image *im;

   re = (Render_Engine *)data;
   if (!image) return NULL;
   im = image;
   if (im->alpha == has_alpha) return image;
   if (im->native.data)
     {
        im->alpha = has_alpha;
        return image;
     }
   eng_window_use(re->win);
   if ((im->tex) && (im->tex->pt->dyn.img))
     {
        im->alpha = has_alpha;
        im->tex->alpha = im->alpha;
        return image;
     }

   if (im->cs.space != EVAS_COLORSPACE_ARGB8888) return im;
   if ((has_alpha) && (im->im->cache_entry.flags.alpha)) return image;
   else if ((!has_alpha) && (!im->im->cache_entry.flags.alpha)) return image;
   if (im->references > 1)
     {
        Evas_GL_Image *im_new;

        if (!im->im->image.data)
          evas_cache_image_load_data(&im->im->cache_entry);
        im_new = evas_gl_common_image_new_from_copied_data
           (im->gc, im->im->cache_entry.w, im->im->cache_entry.h,
               im->im->image.data,
               eng_image_alpha_get(data, image),
               eng_image_colorspace_get(data, image));
        if (!im_new) return im;
        evas_gl_common_image_free(im);
        im = im_new;
     }
   else
     evas_gl_common_image_dirty(im, 0, 0, 0, 0);
   return evas_gl_common_image_alpha_set(im, has_alpha ? 1 : 0);


}
