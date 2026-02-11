Boolean_getBoolean(JNIEnv *env, jobject obj , const char* p0 , jboolean* result, lList **alpp) {
   jgdi_result_t ret = JGDI_SUCCESS;
   static jmethodID mid = NULL;

   jstring p0_obj = NULL;
   jboolean temp = FALSE;

   DENTER(BASIS_LAYER, "Boolean_getBoolean");

   if (result == NULL ) {
      answer_list_add(alpp, "result is NULL", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
      DRETURN(JGDI_ILLEGAL_STATE);
   }

   *result = FALSE;

  if (mid == NULL) {
     if (JGDI_SUCCESS != get_method_id_for_fullClassname(env, obj, &mid, "java/lang/Boolean", "getBoolean", "(Ljava/lang/String;)Z", alpp)) {
        DRETURN(JGDI_ILLEGAL_STATE);
     }
   }

   if (p0 != NULL) {
      p0_obj = (*env)->NewStringUTF(env, p0 );
   }
   temp = (*env)->CallBooleanMethod(env, obj, mid, p0_obj);
   if (test_jni_error(env, "Boolean_getBoolean failed", alpp)) {
      ret = JGDI_ILLEGAL_STATE;
      temp = FALSE;

   }
      *result = temp;

   DRETURN(ret);
}
