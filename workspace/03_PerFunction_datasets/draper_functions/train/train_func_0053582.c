href_list_find_effective_diff(lList **answer_list, const lList *add_groups,
                              const lList *rem_groups, const lList *master_list,
                              lList **add_hosts, lList **rem_hosts)
{
   bool ret = true;

   DENTER(HOSTREF_LAYER, "href_list_find_effective_diff");
   if (ret && add_groups != NULL) {
      ret &= href_list_find_all_references(add_groups, answer_list,
                                           master_list, add_hosts, NULL);
   }
   if (ret && rem_groups != NULL) {
      ret &= href_list_find_all_references(rem_groups, answer_list,
                                           master_list, rem_hosts, NULL);
   }
   if (ret && add_hosts != NULL && *add_hosts != NULL &&
       rem_hosts != NULL && *rem_hosts != NULL) {
      lList *tmp_rem_hosts = NULL;
      lList *tmp_add_hosts = NULL;

      ret &= href_list_find_diff(*add_hosts, answer_list,
                                 *rem_hosts, &tmp_add_hosts,
                                 &tmp_rem_hosts, NULL, NULL);
      if (ret) {
         lFreeList(add_hosts);
         lFreeList(rem_hosts);
         *add_hosts = tmp_add_hosts;
         *rem_hosts = tmp_rem_hosts;
         tmp_add_hosts = NULL;
         tmp_rem_hosts = NULL;
      }
   }
   DEXIT;
   return ret;
}
