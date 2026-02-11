Java_org_gdal_ogr_ogrJNI_DataSource_1ExecuteSQL_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jlong jarg3, jobject jarg3_, jstring jarg4) {
  jlong jresult = 0 ;
  OGRDataSourceShadow *arg1 = (OGRDataSourceShadow *) 0 ;
  char *arg2 = (char *) 0 ;
  OGRGeometryShadow *arg3 = (OGRGeometryShadow *) 0 ;
  char *arg4 = (char *) 0 ;
  OGRLayerShadow *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg3_;
  arg1 = *(OGRDataSourceShadow **)&jarg1;
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  arg3 = *(OGRGeometryShadow **)&jarg3;
  arg4 = 0;
  if (jarg4) {
    arg4 = (char *)jenv->GetStringUTFChars(jarg4, 0);
    if (!arg4) return 0;
  }
  {
    if (!arg2) {
      {
        SWIG_JavaException(jenv, SWIG_ValueError, "Received a NULL pointer."); return 0;
      };
    }
  }
  result = (OGRLayerShadow *)OGRDataSourceShadow_ExecuteSQL__SWIG_0(arg1,(char const *)arg2,arg3,(char const *)arg4);
  *(OGRLayerShadow **)&jresult = result;
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  if (arg4) jenv->ReleaseStringUTFChars(jarg4, (const char *)arg4);
  return jresult;
}
