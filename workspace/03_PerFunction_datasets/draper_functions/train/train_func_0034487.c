Calendar_set_2(JNIEnv *env, jobject obj , jint p0 , jint p1 , jint p2 , jint p3 , jint p4 , jint p5 , lList **alpp) {
   jgdi_result_t ret = JGDI_SUCCESS;
   static jmethodID mid = NULL;

   DENTER(BASIS_LAYER, "Calendar_set_2");

  if (mid == NULL) {
     if (JGDI_SUCCESS != get_method_id_for_fullClassname(env, obj, &mid, "java/util/Calendar", "set", "(IIIIII)V", alpp)) {
        DRETURN(JGDI_ILLEGAL_STATE);
     }
   }

   (*env)->CallVoidMethod(env, obj, mid, p0, p1, p2, p3, p4, p5);
   if (test_jni_error(env, "Calendar_set_2 failed", alpp)) {
      ret = JGDI_ILLEGAL_STATE;

   }    DRETURN(ret);
}
