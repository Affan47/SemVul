Java_org_gdal_gdal_gdalJNI_Driver_1Create_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jint jarg3, jint jarg4, jint jarg5) {
  jlong jresult = 0 ;
  GDALDriverShadow *arg1 = (GDALDriverShadow *) 0 ;
  char *arg2 = (char *) 0 ;
  int arg3 ;
  int arg4 ;
  int arg5 ;
  GDALDatasetShadow *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(GDALDriverShadow **)&jarg1;
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  arg3 = (int)jarg3;
  arg4 = (int)jarg4;
  arg5 = (int)jarg5;
  result = (GDALDatasetShadow *)GDALDriverShadow_Create__SWIG_0(arg1,(char const *)arg2,arg3,arg4,arg5);
  *(GDALDatasetShadow **)&jresult = result;
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}
