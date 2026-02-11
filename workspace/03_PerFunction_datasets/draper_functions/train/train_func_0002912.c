string_list_to_list_elem(JNIEnv *env, jobject list, lList **lpp, lDescr *descr, int nm, lList **alpp) {

   jobject  iter = NULL;
   jboolean has_next = 0;

   DENTER(BASIS_LAYER, "string_list_to_list_elem");

   if (List_iterator(env, list, &iter, alpp) != JGDI_SUCCESS) {
      DRETURN(JGDI_ERROR);
   }

   while (TRUE) {
      if (Iterator_hasNext(env, iter, &has_next, alpp) != JGDI_SUCCESS) {
        DRETURN(JGDI_ERROR);
      } else if (has_next == false) {
         break;
      } else {
         jstring str_obj = NULL;
         if (Iterator_next(env, iter, &str_obj, alpp) != JGDI_SUCCESS) {
            DRETURN(JGDI_ERROR);
         } else {
           const char* str;
           if (str_obj != NULL) {
              str = (*env)->GetStringUTFChars(env, str_obj, 0);
              if (str == NULL) {
                 answer_list_add(alpp, "string_list_to_list_elem: GetStringUTFChars failed. Out of memory.", STATUS_EMALLOC, ANSWER_QUALITY_ERROR);
                 DRETURN(JGDI_ERROR);
              }
           } else {
              str = NULL;
           }
           DPRINTF(("Got %s from list\n", str));
           lAddElemStr(lpp, nm, str, descr);
           if (str) {
               (*env)->ReleaseStringUTFChars(env, str_obj, str);
           }
         }
      }
   }

   DRETURN(JGDI_SUCCESS);
}
