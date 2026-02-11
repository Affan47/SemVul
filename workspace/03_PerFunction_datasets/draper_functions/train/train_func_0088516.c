Java_org_gdal_gdal_gdalJNI_MajorObject_1SetMetadata_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jobject jarg2, jstring jarg3) {
  jint jresult = 0 ;
  GDALMajorObjectShadow *arg1 = (GDALMajorObjectShadow *) 0 ;
  char **arg2 = (char **) 0 ;
  char *arg3 = (char *) 0 ;
  CPLErr result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(GDALMajorObjectShadow **)&jarg1;
  {

    arg2 = NULL;
    if(jarg2 != 0) {
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
      for (jobject keys = jenv->CallObjectMethod(jarg2, elements);
        jenv->CallBooleanMethod(keys, hasMoreElements) == JNI_TRUE;) {
        jstring value = (jstring)jenv->CallObjectMethod(keys, getNextElement);
        if (value == NULL || !jenv->IsInstanceOf(value, stringClass))
        {
          CSLDestroy(arg2);
          SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, "an element in the vector is not a string");
          return 0;
        }
        const char *valptr = jenv->GetStringUTFChars(value, 0);
        arg2 = CSLAddString(arg2,  valptr);
        jenv->ReleaseStringUTFChars(value, valptr);
      }
    }
  }
  arg3 = 0;
  if (jarg3) {
    arg3 = (char *)jenv->GetStringUTFChars(jarg3, 0);
    if (!arg3) return 0;
  }
  result = (CPLErr)GDALMajorObjectShadow_SetMetadata__SWIG_0(arg1,arg2,(char const *)arg3);
  jresult = (jint)result;
  {

    CSLDestroy( arg2 );
  }
  if (arg3) jenv->ReleaseStringUTFChars(jarg3, (const char *)arg3);
  return jresult;
}
