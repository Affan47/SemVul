get_string_list(JNIEnv *env, jobject obj, const char* getter, lList **lpp, lDescr* descr, int nm, lList **alpp) {
   jmethodID get_mid;
   jclass    cls;
   jobject   list;

   DENTER(BASIS_LAYER, "get_string_list");

   cls = (*env)->GetObjectClass(env, obj);
   if (test_jni_error(env, "get_string_list: class for obj not found", alpp)) {
      DRETURN(JGDI_ERROR);
   }

   get_mid = get_methodid(env, cls, getter, "()Ljava/util/List;", alpp);
   if (!get_mid) {
      DRETURN(JGDI_ERROR);
   }

   list = (*env)->CallObjectMethod(env, obj, get_mid);
   if (test_jni_error(env, "get_string_list: call of getter failed", alpp)) {
      DRETURN(JGDI_ERROR);
   }

   if (string_list_to_list_elem(env, list, lpp, descr, nm, alpp) != JGDI_SUCCESS) {
      DRETURN(JGDI_ERROR);
   }

   DRETURN(JGDI_SUCCESS);
}
