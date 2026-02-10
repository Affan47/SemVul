cqueue_verify_attributes(lListElem *cqueue, lList **answer_list,
                         lListElem *reduced_elem, bool in_master)
{
   bool ret = true;

   DENTER(CQUEUE_LAYER, "cqueue_verify_attributes");
   if (cqueue != NULL && reduced_elem != NULL) {
      int index = 0;

      while (cqueue_attribute_array[index].cqueue_attr != NoName && ret) {
         int pos = lGetPosViaElem(reduced_elem,
                                  cqueue_attribute_array[index].cqueue_attr, SGE_NO_ABORT);

         if (pos >= 0) {
            lList *list = NULL;

            list = lGetList(cqueue,
                            cqueue_attribute_array[index].cqueue_attr);


            if (ret) {
               lListElem *elem = lGetElemHost(list,
                   cqueue_attribute_array[index].href_attr, HOSTREF_DEFAULT);

               if (elem == NULL) {
                  SGE_ADD_MSG_ID(sprintf(SGE_EVENT,
                                 MSG_CQUEUE_NODEFVALUE_S,
                                 cqueue_attribute_array[index].name));
                  answer_list_add(answer_list, SGE_EVENT,
                                  STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
                  ret = false;
               }
            }


            if (ret) {
               lListElem *elem = NULL;

               for_each(elem, list) {
                  const char *hostname = NULL;
                  const void *iterator = NULL;
                  lListElem *first_elem = NULL;

                  hostname = lGetHost(elem,
                        cqueue_attribute_array[index].href_attr);
                  first_elem = lGetElemHostFirst(list,
                        cqueue_attribute_array[index].href_attr,
                        hostname, &iterator);

                  if (elem != first_elem) {
                     SGE_ADD_MSG_ID(sprintf(SGE_EVENT,
                                   MSG_CQUEUE_MULVALNOTALLOWED_S, hostname));
                     answer_list_add(answer_list, SGE_EVENT,
                                     STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
                     ret = false;
                     break;
                  }
                  if (is_hgroup_name(hostname)) {
                     if (in_master && strcmp(hostname, HOSTREF_DEFAULT)) {
                        const lList *master_list =
                              *(object_type_get_master_list(SGE_TYPE_HGROUP));
                        const lListElem *hgroup =
                                    hgroup_list_locate(master_list, hostname);

                        if (hgroup == NULL) {
                           ERROR((SGE_EVENT, MSG_CQUEUE_INVALIDDOMSETTING_SS,
                                  cqueue_attribute_array[index].name,
                                  hostname));
                           answer_list_add(answer_list, SGE_EVENT,
                                         STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
                           ret = false;
                           break;
                        }
                     }
                  } else {
                     char resolved_name[CL_MAXHOSTLEN+1];
                     int back = getuniquehostname(hostname, resolved_name, 0);

                     if (back == CL_RETVAL_OK) {
                        lSetHost(elem,
                                 cqueue_attribute_array[index].href_attr,
                                 resolved_name);
                     } else {


                     }
                  }
               }
            }


            if (ret &&
                cqueue_attribute_array[index].verify_function != NULL &&
                (cqueue_attribute_array[index].verify_client || in_master)) {
               lListElem *elem = NULL;

               for_each(elem, list) {
                  ret &= cqueue_attribute_array[index].
                                 verify_function(cqueue, answer_list, elem);
               }
            }
         }

         index++;
      }
   }
   DEXIT;
   return ret;
}
