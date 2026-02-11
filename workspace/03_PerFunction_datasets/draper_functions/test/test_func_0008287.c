Java_org_gdal_gdal_gdalJNI_Rename(JNIEnv *jenv, jclass jcls, jstring jarg1, jstring jarg2) {
  jint jresult = 0 ;
  char *arg1 = (char *) 0 ;
  char *arg2 = (char *) 0 ;
  int result;

  (void)jenv;
  (void)jcls;
  arg1 = 0;
  if (jarg1) {
    arg1 = (char *)jenv->GetStringUTFChars(jarg1, 0);
    if (!arg1) return 0;
  }
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  result = (int)VSIRename((char const *)arg1,(char const *)arg2);
  jresult = (jint)result;
  if (arg1) jenv->ReleaseStringUTFChars(jarg1, (const char *)arg1);
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}
