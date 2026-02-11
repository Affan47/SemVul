eglGetCurrentContext(void)
{
   _EGLContext *ctx = _eglGetCurrentContext();
   EGLContext ret;

   ret = _eglGetContextHandle(ctx);

   RETURN_EGL_SUCCESS(NULL, ret);
}
