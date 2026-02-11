eglQueryAPI(void)
{
   _EGLThreadInfo *t = _eglGetCurrentThread();
   EGLenum ret;


   ret = _eglConvertApiFromIndex(t->CurrentAPIIndex);

   RETURN_EGL_SUCCESS(NULL, ret);
}
