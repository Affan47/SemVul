ensureHandlersSetup(JNIEnv *env) {
   if (!isHandlersSetup) {
      int ok = 1;

      cpl_init(CPL_INIT_DEFAULT);

      if (cpl_error_get_code()) {
          cpl_msg_warning("Java CPL", "CPL initialization failed: '%s' at %s\n",
                          cpl_error_get_message(), cpl_error_get_where());
      } else {
          (void)setCplMessaging(CPL_TRUE);
      }

#ifndef GASGANO_HAS_NO_CPL_EXCEPTION_HANDLER
      if (cpl_error_get_code() && !(*env)->ExceptionCheck(env)) {


          (*env)->ThrowNew(env, CPLExceptionClass, "CPL initialization failed");
      }
#endif
      inistate = cpl_errorstate_get();
      isHandlersSetup = ok;
   }
   return isHandlersSetup;
}
