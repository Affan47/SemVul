Java_org_gdal_gdal_gdalJNI_GetLastErrorMsg(JNIEnv *jenv, jclass jcls) {
  jstring jresult = 0 ;
  char *result = 0 ;

  (void)jenv;
  (void)jcls;
  result = (char *)CPLGetLastErrorMsg();
  if (result) jresult = jenv->NewStringUTF((const char *)result);
  return jresult;
}
