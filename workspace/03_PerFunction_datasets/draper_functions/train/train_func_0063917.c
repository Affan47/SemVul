Class_isAssignableFrom(JNIEnv *env, jobject obj , jobject p0 , jboolean* result, lList **alpp) {
   jgdi_result_t ret = JGDI_SUCCESS;
   static jmethodID mid = NULL;

   jboolean temp = FALSE;

   DENTER(BASIS_LAYER, "Class_isAssignableFrom");

   if (result == NULL ) {
      answer_list_add(alpp, "result is NULL", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
      DRETURN(JGDI_ILLEGAL_STATE);
   }

   *result = FALSE;

  if (mid == NULL) {
     if (JGDI_SUCCESS != get_method_id_for_fullClassname(env, obj, &mid, "java/lang/Class", "isAssignableFrom", "(Ljava/lang/Class;)Z", alpp)) {
        DRETURN(JGDI_ILLEGAL_STATE);
     }
   }

   temp = (*env)->CallBooleanMethod(env, obj, mid, p0);
   if (test_jni_error(env, "Class_isAssignableFrom failed", alpp)) {
      ret = JGDI_ILLEGAL_STATE;
      temp = FALSE;

   }
      *result = temp;

   DRETURN(ret);
}
