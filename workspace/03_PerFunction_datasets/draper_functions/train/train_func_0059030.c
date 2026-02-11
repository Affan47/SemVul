find_logger_class(JNIEnv *env)
{
   static jclass clazz = NULL;

   if( clazz == NULL) {
      jclass tmpclazz = (*env)->FindClass(env, "java/util/logging/Logger");
      if (tmpclazz == NULL) {
         abort();
      }

      clazz = (jclass)(*env)->NewGlobalRef(env, tmpclazz);
      if (clazz == NULL) {
         abort();
      }
   }
   return clazz;
}
