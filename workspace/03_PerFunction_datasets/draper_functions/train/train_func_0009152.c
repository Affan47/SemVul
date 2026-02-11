Java_org_gdal_gdal_gdalJNI_RegenerateOverview_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_, jstring jarg3) {
  jint jresult = 0 ;
  GDALRasterBandShadow *arg1 = (GDALRasterBandShadow *) 0 ;
  GDALRasterBandShadow *arg2 = (GDALRasterBandShadow *) 0 ;
  char *arg3 = (char *) 0 ;
  int result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(GDALRasterBandShadow **)&jarg1;
  arg2 = *(GDALRasterBandShadow **)&jarg2;
  arg3 = 0;
  if (jarg3) {
    arg3 = (char *)jenv->GetStringUTFChars(jarg3, 0);
    if (!arg3) return 0;
  }
  {
    if (!arg1) {
      {
        SWIG_JavaException(jenv, SWIG_ValueError, "Received a NULL pointer."); return 0;
      };
    }
  }
  {
    if (!arg2) {
      {
        SWIG_JavaException(jenv, SWIG_ValueError, "Received a NULL pointer."); return 0;
      };
    }
  }
  result = (int)RegenerateOverview(arg1,arg2,(char const *)arg3);
  jresult = (jint)result;
  if (arg3) jenv->ReleaseStringUTFChars(jarg3, (const char *)arg3);
  return jresult;
}
