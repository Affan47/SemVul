makeLTDLException(JNIEnv *env) {
   const char *msg;
   jstring jMsg;
   jthrowable error = (jthrowable)0;


   if (!ensureConstantsSetup(env)) {
      error = (*env)->ExceptionOccurred(env);
      (*env)->ExceptionClear(env);
      return error;
   }


   msg = lt_dlerror();
   if (!msg) {
      msg = "no error";
   }
   jMsg = (*env)->NewStringUTF(env, msg);
   if (jMsg) {
      error = (*env)->NewObject(env, LTDLExceptionClass,
                                LTDLExceptionConstructor, jMsg);
   }


   if (!error) {
      error = (*env)->ExceptionOccurred(env);
      (*env)->ExceptionClear(env);
   }


   return error;
}
