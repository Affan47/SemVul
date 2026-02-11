Java_org_gdal_gdal_gdalJNI_ComputeProximity_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_, jobject jarg3, jobject jarg4) {
  jint jresult = 0 ;
  GDALRasterBandShadow *arg1 = (GDALRasterBandShadow *) 0 ;
  GDALRasterBandShadow *arg2 = (GDALRasterBandShadow *) 0 ;
  char **arg3 = (char **) 0 ;
  GDALProgressFunc arg4 ;
  void *arg5 = (void *) 0 ;
  int result;

  (void)jenv;
  (void)jcls;
  JavaProgressData sProgressInfo;
  sProgressInfo.jenv = jenv;
  sProgressInfo.pJavaCallback = NULL;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(GDALRasterBandShadow **)&jarg1;
  arg2 = *(GDALRasterBandShadow **)&jarg2;
  {

    arg3 = NULL;
    if(jarg3 != 0) {
      const jclass vector = jenv->FindClass("java/util/Vector");
      const jclass enumeration = jenv->FindClass("java/util/Enumeration");
      const jclass stringClass = jenv->FindClass("java/lang/String");
      const jmethodID elements = jenv->GetMethodID(vector, "elements",
        "()Ljava/util/Enumeration;");
      const jmethodID hasMoreElements = jenv->GetMethodID(enumeration,
        "hasMoreElements", "()Z");
      const jmethodID getNextElement = jenv->GetMethodID(enumeration,
        "nextElement", "()Ljava/lang/Object;");
      if(vector == NULL || enumeration == NULL || elements == NULL ||
        hasMoreElements == NULL || getNextElement == NULL) {
        fprintf(stderr, "Could not load (options **) jni types.\n");
        return 0;
      }
      for (jobject keys = jenv->CallObjectMethod(jarg3, elements);
        jenv->CallBooleanMethod(keys, hasMoreElements) == JNI_TRUE;) {
        jstring value = (jstring)jenv->CallObjectMethod(keys, getNextElement);
        if (value == NULL || !jenv->IsInstanceOf(value, stringClass))
        {
          CSLDestroy(arg3);
          SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, "an element in the vector is not a string");
          return 0;
        }
        const char *valptr = jenv->GetStringUTFChars(value, 0);
        arg3 = CSLAddString(arg3,  valptr);
        jenv->ReleaseStringUTFChars(value, valptr);
      }
    }
  }
  {
    if ( jarg4 != 0 ) {
      sProgressInfo.pJavaCallback = jarg4;
      arg4 = JavaProgressProxy;
      arg5 = &sProgressInfo;
    }
    else
    {
      arg4 = NULL;
      arg5 = NULL;
    }
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
  result = (int)ComputeProximity(arg1,arg2,arg3,arg4,arg5);
  jresult = (jint)result;
  {

    CSLDestroy( arg3 );
  }
  return jresult;
}
