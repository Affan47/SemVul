_eglGetConfigAttrib(_EGLDriver *drv, _EGLDisplay *dpy, _EGLConfig *conf,
                    EGLint attribute, EGLint *value)
{
   if (!_eglIsConfigAttribValid(conf, attribute))
      return _eglError(EGL_BAD_ATTRIBUTE, "eglGetConfigAttrib");


   switch (attribute) {
   case EGL_MATCH_NATIVE_PIXMAP:
      return _eglError(EGL_BAD_ATTRIBUTE, "eglGetConfigAttrib");
      break;
   default:
      break;
   }

   if (!value)
      return _eglError(EGL_BAD_PARAMETER, "eglGetConfigAttrib");

   *value = _eglGetConfigKey(conf, attribute);
   return EGL_TRUE;
}
