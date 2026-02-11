Java_org_gdal_gdal_gdalJNI_Transformer_1TransformPoint_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jdoubleArray jarg2, jint jarg3, jdouble jarg4, jdouble jarg5, jdouble jarg6) {
  jint jresult = 0 ;
  GDALTransformerInfoShadow *arg1 = (GDALTransformerInfoShadow *) 0 ;
  double *arg2 ;
  int arg3 ;
  double arg4 ;
  double arg5 ;
  double arg6 ;
  int result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(GDALTransformerInfoShadow **)&jarg1;
  {

    if(jarg2 == NULL || jenv->GetArrayLength(jarg2) != 3) {
      char errorMsg[512];
      sprintf(errorMsg, "array of size %d expected", 3);
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, errorMsg);
      return 0;
    }
    arg2 = (double *)jenv->GetDoubleArrayElements(jarg2, NULL);
  }
  arg3 = (int)jarg3;
  arg4 = (double)jarg4;
  arg5 = (double)jarg5;
  arg6 = (double)jarg6;
  result = (int)GDALTransformerInfoShadow_TransformPoint__SWIG_1(arg1,arg2,arg3,arg4,arg5,arg6);
  jresult = (jint)result;
  {

  }
  {

    jenv->ReleaseDoubleArrayElements(jarg2, (jdouble *)arg2, 0);
  }
  return jresult;
}
