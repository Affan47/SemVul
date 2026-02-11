Java_org_gdal_gdal_gdalJNI_MajorObject_1GetMetadataItem_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jstring jarg3) {
  jstring jresult = 0 ;
  GDALMajorObjectShadow *arg1 = (GDALMajorObjectShadow *) 0 ;
  char *arg2 = (char *) 0 ;
  char *arg3 = (char *) 0 ;
  char *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(GDALMajorObjectShadow **)&jarg1;
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  arg3 = 0;
  if (jarg3) {
    arg3 = (char *)jenv->GetStringUTFChars(jarg3, 0);
    if (!arg3) return 0;
  }
  {
    if (!arg2) {
      {
        SWIG_JavaException(jenv, SWIG_ValueError, "Received a NULL pointer."); return 0;
      };
    }
  }
  result = (char *)GDALMajorObjectShadow_GetMetadataItem__SWIG_0(arg1,(char const *)arg2,(char const *)arg3);
  if (result) jresult = jenv->NewStringUTF((const char *)result);
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  if (arg3) jenv->ReleaseStringUTFChars(jarg3, (const char *)arg3);
  return jresult;
}
