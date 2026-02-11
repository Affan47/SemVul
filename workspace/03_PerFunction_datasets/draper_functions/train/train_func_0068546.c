_eglSetLogProc(_EGLLogProc logger)
{
   EGLint num_messages = 0;

   _eglLockMutex(&logging.mutex);

   if (logging.logger != logger) {
      logging.logger = logger;

      num_messages = logging.num_messages;
      logging.num_messages = 0;
   }

   _eglUnlockMutex(&logging.mutex);

   if (num_messages)
      _eglLog(_EGL_DEBUG,
              "New logger installed. "
              "Messages before the new logger might not be available.");
}
