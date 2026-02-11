Java_org_gdal_ogr_ogrJNI_DataSource_1ExecuteSQL_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2) {
  jlong jresult = 0 ;
  OGRDataSourceShadow *arg1 = (OGRDataSourceShadow *) 0 ;
  char *arg2 = (char *) 0 ;
  OGRLayerShadow *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(OGRDataSourceShadow **)&jarg1;
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  {
    if (!arg2) {
      {
        SWIG_JavaException(jenv, SWIG_ValueError, "Received a NULL pointer."); return 0;
      };
    }
  }
  result = (OGRLayerShadow *)OGRDataSourceShadow_ExecuteSQL__SWIG_0(arg1,(char const *)arg2);
  *(OGRLayerShadow **)&jresult = result;
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}
