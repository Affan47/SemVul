hgroup_find_all_referencees(const lListElem *this_elem,
                            lList **answer_list, const lList *master_list,
                            lList **occupants_groups)
{
   bool ret = true;

   DENTER(HGROUP_LAYER, "hgroup_find_all_referencees");
   if (this_elem != NULL && occupants_groups != NULL) {
      lList *href_list = NULL;
      const char *name;

      name = lGetHost(this_elem, HGRP_name);
      ret &= href_list_add(&href_list, answer_list, name);

      if (ret) {
         ret &= href_list_find_all_referencees(href_list, answer_list,
                                             master_list, occupants_groups);
      }
      lFreeList(&href_list);
   }
   DEXIT;
   return ret;
}
