Java_org_gdal_gdal_gdalJNI_Band_1GetOffset(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jobjectArray jarg2) {
  GDALRasterBandShadow *arg1 = (GDALRasterBandShadow *) 0 ;
  double *arg2 = (double *) 0 ;
  int *arg3 = (int *) 0 ;
  double tmpval2 ;
  int tmphasval2 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(GDALRasterBandShadow **)&jarg1;
  {

    arg2 = &tmpval2;
    arg3 = &tmphasval2;
    if(jarg2 == NULL || jenv->GetArrayLength(jarg2) < 1) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array or empty array");
      return ;
    }
  }
  GDALRasterBandShadow_GetOffset(arg1,arg2,arg3);
  {

    const jclass Double = jenv->FindClass("java/lang/Double");
    const jmethodID ctor = jenv->GetMethodID(Double, "<init>",
      "(D)V");
    if(*arg3) {
      jobject dbl = jenv->NewObject(Double, ctor, tmpval2);
      jenv->SetObjectArrayElement(jarg2, (jsize)0, dbl);
    } else {
      jenv->SetObjectArrayElement(jarg2, (jsize)0, 0);
    }
  }
}
