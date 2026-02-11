eng_gl_native_surface_get(void *data __UNUSED__, void *surface, void *native_surface)
{
   Render_Engine_GL_Surface *sfc;
   Evas_Native_Surface *ns;

   sfc = (Render_Engine_GL_Surface*)surface;
   ns  = (Evas_Native_Surface*)native_surface;

   if (sfc->direct_fb_opt)
     {
        ns->type = EVAS_NATIVE_SURFACE_OPENGL;
        ns->version = EVAS_NATIVE_SURFACE_VERSION;
        ns->data.opengl.texture_id = sfc->rt_tex;
        ns->data.opengl.framebuffer_id = 0;
        ns->data.opengl.x = 0;
        ns->data.opengl.y = 0;
        ns->data.opengl.w = sfc->w;
        ns->data.opengl.h = sfc->h;
     }
   else
     {
        ns->type = EVAS_NATIVE_SURFACE_OPENGL;
        ns->version = EVAS_NATIVE_SURFACE_VERSION;
        ns->data.opengl.texture_id = sfc->rt_tex;
        ns->data.opengl.framebuffer_id = sfc->rt_tex;
        ns->data.opengl.x = 0;
        ns->data.opengl.y = 0;
        ns->data.opengl.w = sfc->w;
        ns->data.opengl.h = sfc->h;
     }

   return 1;
}
