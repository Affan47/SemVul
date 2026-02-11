cqueue_verify_subordinate_list(lListElem *cqueue, lList **answer_list,
                               lListElem *attr_elem)
{
   bool ret = true;

   DENTER(CQUEUE_VERIFY_LAYER, "cqueue_verify_subordinate_list");
   if (cqueue != NULL && attr_elem != NULL) {
      const lList *master_list =
                           *(object_type_get_master_list(SGE_TYPE_CQUEUE));
      const char *cqueue_name = lGetString(cqueue, CQ_name);
      lList *so_list = lGetList(attr_elem, ASOLIST_value);
      lListElem *so;

      for_each(so, so_list) {
         const char *so_name = lGetString(so, SO_name);


         if (strcmp(cqueue_name, so_name) != 0) {
            const lListElem *cqueue = NULL;


            cqueue = cqueue_list_locate(master_list, so_name);
            if (cqueue != NULL) {


               ;
            } else {
               ERROR((SGE_EVENT, MSG_CQUEUE_UNKNOWNSUB_SS,
                      so_name, cqueue_name));
               answer_list_add(answer_list, SGE_EVENT,
                               STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
               ret = false;
            }
         } else {
            ERROR((SGE_EVENT, MSG_CQUEUE_SUBITSELF_S, cqueue_name));
            answer_list_add(answer_list, SGE_EVENT,
                            STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
            ret = false;
         }
      }
   }
   DEXIT;
   return ret;
}
