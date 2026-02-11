answer_list_log(lList **answer_list, bool is_free_list, bool show_info) {

   bool ret = false;
   lListElem *answer;

   DENTER(ANSWER_LAYER, "answer_list_log");

   if (answer_list != NULL && *answer_list != NULL) {
      for_each(answer, *answer_list) {
         ret = answer_log(answer, show_info);
      }
      if (is_free_list) {
         lFreeList(answer_list);
      }
   }

   DEXIT;
   return ret;
}
