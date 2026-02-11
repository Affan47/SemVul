_eglCheckDisplayHandle(EGLDisplay dpy)
{
   _EGLDisplay *cur;

   _eglLockMutex(_eglGlobal.Mutex);
   cur = _eglGlobal.DisplayList;
   while (cur) {
      if (cur == (_EGLDisplay *) dpy)
         break;
      cur = cur->Next;
   }
   _eglUnlockMutex(_eglGlobal.Mutex);
   return (cur != NULL);
}
