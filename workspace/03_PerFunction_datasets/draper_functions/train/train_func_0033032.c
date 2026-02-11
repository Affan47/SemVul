Java_org_gdal_osr_osrJNI_SpatialReference_1SetGeogCS_1_1SWIG_13(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jstring jarg3, jstring jarg4, jdouble jarg5, jdouble jarg6, jstring jarg7) {
  jint jresult = 0 ;
  OSRSpatialReferenceShadow *arg1 = (OSRSpatialReferenceShadow *) 0 ;
  char *arg2 = (char *) 0 ;
  char *arg3 = (char *) 0 ;
  char *arg4 = (char *) 0 ;
  double arg5 ;
  double arg6 ;
  char *arg7 = (char *) 0 ;
  OGRErr result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(OSRSpatialReferenceShadow **)&jarg1;
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
  arg4 = 0;
  if (jarg4) {
    arg4 = (char *)jenv->GetStringUTFChars(jarg4, 0);
    if (!arg4) return 0;
  }
  arg5 = (double)jarg5;
  arg6 = (double)jarg6;
  arg7 = 0;
  if (jarg7) {
    arg7 = (char *)jenv->GetStringUTFChars(jarg7, 0);
    if (!arg7) return 0;
  }
  result = (OGRErr)OSRSpatialReferenceShadow_SetGeogCS__SWIG_0(arg1,(char const *)arg2,(char const *)arg3,(char const *)arg4,arg5,arg6,(char const *)arg7);
  {

    if (result != 0 && bUseExceptions) {
      SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException,
        OGRErrMessages(result));
      return 0;
    }
    jresult = (jint)result;
  }
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  if (arg3) jenv->ReleaseStringUTFChars(jarg3, (const char *)arg3);
  if (arg4) jenv->ReleaseStringUTFChars(jarg4, (const char *)arg4);
  if (arg7) jenv->ReleaseStringUTFChars(jarg7, (const char *)arg7);
  {


  }
  return jresult;
}
