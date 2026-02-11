cqueue_verify_consumable_config_list(lListElem *cqueue, lList **answer_list,
                                     lListElem *attr_elem)
{
   bool ret = true;

   DENTER(CQUEUE_VERIFY_LAYER, "cqueue_verify_project_list");
   if (cqueue != NULL && attr_elem != NULL) {
      lList *centry_list = lGetList(attr_elem, ACELIST_value);

      if (centry_list != NULL) {
         const lList *master_list = *(centry_list_get_master_list());

         if (!centry_list_do_all_exists(master_list, answer_list, centry_list)) {
            ret = false;
         }
      }
   }
   DEXIT;
   return ret;
}
