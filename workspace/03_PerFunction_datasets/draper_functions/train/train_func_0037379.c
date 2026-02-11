Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1strerror(JNIEnv *jenv, jclass jcls, jint jarg1) {
  jstring jresult = 0 ;
  int arg1 ;
  char *result = 0 ;

  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1;
  result = (char *)DbEnv_strerror(arg1);
  if (result) jresult = (*jenv)->NewStringUTF(jenv, (const char *)result);
  return jresult;
}
