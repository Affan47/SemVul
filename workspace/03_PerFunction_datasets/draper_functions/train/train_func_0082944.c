Java_org_gdal_ogr_ogrJNI_Geometry_1GetEnvelope(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jdoubleArray jarg2) {
  OGRGeometryShadow *arg1 = (OGRGeometryShadow *) 0 ;
  double *arg2 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(OGRGeometryShadow **)&jarg1;
  {

    if(jarg2 == NULL || jenv->GetArrayLength(jarg2) != 4) {
      char errorMsg[512];
      sprintf(errorMsg, "array of size %d expected", 4);
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, errorMsg);
      return ;
    }
    arg2 = (double *)jenv->GetDoubleArrayElements(jarg2, NULL);
  }
  OGRGeometryShadow_GetEnvelope(arg1,arg2);
  {

  }
  {

    jenv->ReleaseDoubleArrayElements(jarg2, (jdouble *)arg2, 0);
  }
}
