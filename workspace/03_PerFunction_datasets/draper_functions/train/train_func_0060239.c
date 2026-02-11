plugin_search(const char *search_string, int case_sense,
                  struct search_result **sr)
{
   struct MyKeyRing *mkr_list;
   struct MyKeyRing *temp_list;
   struct MyKeyRing mkr;
   int num, count;
   char *line;

   jp_logf(JP_LOG_DEBUG, "KeyRing: plugin_search\n");

   *sr=NULL;
   mkr_list=NULL;

   if (!plugin_active) {
      return 0;
   }


   num = get_keyring(&mkr_list, CATEGORY_ALL);
   if (-1 == num)
      return 0;

   count = 0;


   for (temp_list = mkr_list; temp_list; temp_list = temp_list->next) {
      mkr = *temp_list;
      line = NULL;


      if (jp_strstr(mkr.kr.name, search_string, case_sense))
         line = mkr.kr.name;


      if (jp_strstr(mkr.kr.account, search_string, case_sense))
         line = mkr.kr.account;


      if (jp_strstr(mkr.kr.password, search_string, case_sense))
         line = mkr.kr.password;


      if (jp_strstr(mkr.kr.note, search_string, case_sense))
         line = mkr.kr.note;

      if (line) {

         jp_logf(JP_LOG_DEBUG, "KeyRing: calling add_search_result\n");
         add_search_result(line, mkr.unique_id, sr);
         jp_logf(JP_LOG_DEBUG, "KeyRing: back from add_search_result\n");
         count++;
      }
   }

   free_mykeyring_list(&mkr_list);

   return count;
}
