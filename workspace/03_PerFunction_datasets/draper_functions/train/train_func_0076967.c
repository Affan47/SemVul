_eglCheckMode(_EGLDisplay *disp, _EGLMode *m, const char *msg)
{
   _EGLDriver *drv = _eglCheckDisplay(disp, msg);
   if (!drv)
      return NULL;
   if (!m) {
      _eglError(EGL_BAD_MODE_MESA, msg);
      return NULL;
   }
   return drv;
}
