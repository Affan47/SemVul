get_string(JNIEnv *env, jclass bean_class, jobject obj, const char* property_name, char **retstr, lList **alpp) {
   char buf[1024];
   jmethodID mid = NULL;
   jstring jstr;
   const char *name = NULL;

   DENTER(BASIS_LAYER, "get_string");

   sprintf(buf, "get%c%s", toupper(property_name[0]), &property_name[1]);
   mid = get_methodid(env, bean_class, buf, "()Ljava/lang/String;", alpp);
   if (!mid) {
      *retstr = NULL;
      DRETURN(JGDI_ERROR);
   }

   jstr = (jstring) (*env)->CallObjectMethod(env, obj, mid);
   if (test_jni_error(env, "get_string: CallObjectMethod failed", alpp)) {
      *retstr = NULL;
      DRETURN(JGDI_ERROR);
   }

   if (jstr == NULL) {
      *retstr = NULL;
   } else {
      name = (*env)->GetStringUTFChars(env, jstr, 0);
      if (name == NULL) {
         answer_list_add(alpp, "get_string: GetStringUTFChars failed. Out of memory.", STATUS_EMALLOC, ANSWER_QUALITY_ERROR);
         DRETURN(JGDI_ERROR);
      }
      *retstr = strdup(name);
      (*env)->ReleaseStringUTFChars(env, jstr, name);
   }

   DRETURN(JGDI_SUCCESS);
}
