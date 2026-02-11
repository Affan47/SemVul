eng_gl_img_obj_set(void *data, void *image, int has_alpha)
{
   Render_Engine *re = (Render_Engine *)data;

   gl_direct_img_obj = NULL;


   if ((has_alpha) || (re->win->gl_context->rot!=0))
     {
        if (gl_direct_override)
           gl_direct_img_obj = image;
     }
   else
      gl_direct_img_obj = image;
}
