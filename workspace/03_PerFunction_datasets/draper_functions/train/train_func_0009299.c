_eglQueryContext(_EGLDriver *drv, _EGLDisplay *dpy, _EGLContext *c,
                 EGLint attribute, EGLint *value)
{
   (void) drv;
   (void) dpy;

   if (!value)
      return _eglError(EGL_BAD_PARAMETER, "eglQueryContext");

   switch (attribute) {
   case EGL_CONFIG_ID:
      if (!c->Config)
         return _eglError(EGL_BAD_ATTRIBUTE, "eglQueryContext");
      *value = c->Config->ConfigID;
      break;
   case EGL_CONTEXT_CLIENT_VERSION:
      *value = c->ClientMajorVersion;
      break;
   case EGL_CONTEXT_CLIENT_TYPE:
      *value = c->ClientAPI;
      break;
   case EGL_RENDER_BUFFER:
      *value = _eglQueryContextRenderBuffer(c);
      break;
   default:
      return _eglError(EGL_BAD_ATTRIBUTE, "eglQueryContext");
   }

   return EGL_TRUE;
}
