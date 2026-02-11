pipe_vmwgfx_create_screen(int fd)
{
#if _EGL_PIPE_VMWGFX
   struct svga_winsys_screen *sws;
   struct pipe_screen *screen;

   sws = svga_drm_winsys_screen_create(fd);
   if (!sws)
      return NULL;

   screen = svga_screen_create(sws);
   if (!screen)
      return NULL;

   screen = debug_screen_wrap(screen);

   return screen;
#else
   return NULL;
#endif
}
