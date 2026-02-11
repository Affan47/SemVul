href_list_find_all_references(const lList *this_list, lList **answer_list,
                              const lList *master_list, lList **used_hosts,
                              lList **used_groups)
{
   bool ret = true;

   DENTER(HOSTREF_LAYER, "href_list_find_all_references");
   if (this_list != NULL && master_list != NULL) {
      lList *tmp_used_groups = NULL;
      bool free_tmp_list = false;

      if (used_groups == NULL) {
         used_groups = &tmp_used_groups;
         free_tmp_list = true;
      }


      ret &= href_list_find_references(this_list, answer_list, master_list,
                                       used_hosts, used_groups);


      if (ret && used_groups != NULL && *used_groups != NULL) {
         lList *used_sub_groups = NULL;
         lList *used_sub_hosts = NULL;

         ret &= href_list_find_all_references(*used_groups, answer_list,
                                              master_list, &used_sub_hosts,
                                              &used_sub_groups);
         if (ret) {
            if (used_hosts != NULL && used_sub_hosts != NULL) {
               if (*used_hosts != NULL) {
                  lAddList(*used_hosts, &used_sub_hosts);
               } else {
                  *used_hosts = used_sub_hosts;
                  used_sub_hosts = NULL;
               }
            }
            if (used_groups != NULL && used_sub_groups != NULL) {
               if (*used_groups != NULL) {
                  lAddList(*used_groups, &used_sub_groups);
               } else {
                  *used_groups = used_sub_groups;
                  used_sub_groups = NULL;
               }
            }
         }
      }

      if (free_tmp_list) {
         lFreeList(&tmp_used_groups);
      }
   }
   DEXIT;
   return ret;
}
