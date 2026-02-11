Java_com_tresys_setools_apol_apolJNI_apol_1string_1vector_1t_1get_1element(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2) {
  jstring jresult = 0 ;
  apol_string_vector_t *arg1 = (apol_string_vector_t *) 0 ;
  size_t arg2 ;
  char *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(apol_string_vector_t **)&jarg1;
  arg2 = (size_t)jarg2;
  {
    apol_global_jenv = jenv;
    result = (char *)apol_string_vector_t_get_element(arg1,arg2);
  }
  if (result) jresult = (*jenv)->NewStringUTF(jenv, (const char *)result);
  return jresult;
}
