GetGLXScreenConfigs(Display * dpy, int scrn)
{
   struct glx_display *const priv = __glXInitialize(dpy);

   return (priv
           && priv->screens !=
           NULL) ? priv->screens[scrn] : NULL;
}
