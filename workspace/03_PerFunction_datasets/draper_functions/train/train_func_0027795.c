Java_org_gdal_ogr_ogrJNI_new_1FieldDefn_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jstring jarg1, jint jarg2) {
  jlong jresult = 0 ;
  char *arg1 = (char *) 0 ;
  OGRFieldType arg2 ;
  OGRFieldDefnShadow *result = 0 ;

  (void)jenv;
  (void)jcls;
  arg1 = 0;
  if (jarg1) {
    arg1 = (char *)jenv->GetStringUTFChars(jarg1, 0);
    if (!arg1) return 0;
  }
  arg2 = (OGRFieldType)jarg2;
  result = (OGRFieldDefnShadow *)new_OGRFieldDefnShadow__SWIG_0((char const *)arg1,arg2);
  *(OGRFieldDefnShadow **)&jresult = result;
  if (arg1) jenv->ReleaseStringUTFChars(jarg1, (const char *)arg1);
  return jresult;
}
