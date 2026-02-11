get_method_id_for_fullClassname(JNIEnv *env, jobject obj, jmethodID *midref, const char *fullClassname,
                                      const char *methodName, const char *methodSignature, lList **alpp) {

   jclass clazz = NULL;

   DENTER(BASIS_LAYER, "get_method_id_for_fullClassname");


   if (env == NULL) {
      answer_list_add(alpp, "env is NULL", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
      DEXIT;
      return JGDI_NULL_POINTER;
   }
   if (obj == NULL) {
      answer_list_add(alpp, "obj is NULL", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
      DEXIT;
      return JGDI_NULL_POINTER;
   }
   if (midref == NULL) {
      answer_list_add(alpp, "midref is NULL", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
      DEXIT;
      return JGDI_NULL_POINTER;
   }

   clazz = find_class(env, fullClassname, alpp);
   if (clazz == NULL) {
      answer_list_add_sprintf(alpp, STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR,
                              "class %s not found", fullClassname);
      DEXIT;
      return JGDI_ILLEGAL_STATE;
   }
   if (!(*env)->IsInstanceOf(env, obj, clazz)) {
      answer_list_add_sprintf(alpp, STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR,
                      "obj is not an instanceof %s", fullClassname);
      DEXIT;
      return JGDI_ILLEGAL_STATE;
   }

   *midref = get_methodid(env, clazz, methodName, methodSignature, alpp);
   if (*midref == NULL) {
      DEXIT;
      return JGDI_ILLEGAL_STATE;
   }

   DEXIT;
   return JGDI_SUCCESS;
}
