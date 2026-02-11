lockEVC(const char *func, int index, sge_evc_elem_t **outelem, lList **alpp) {

   jgdi_result_t ret = JGDI_SUCCESS;

   DENTER(JGDI_LAYER, "lockEVC");
   if (index >= 0 && index < MAX_EVC_ARRAY_SIZE) {
      sge_evc_elem_t *elem = &sge_evc_array[index];

      pthread_mutex_lock(&(elem->elem_mutex));
      if (elem->sge_evc == NULL) {
         *outelem = NULL;

         pthread_mutex_unlock(&(elem->elem_mutex));
         answer_list_add_sprintf(alpp, STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR,
                                "event client sge_evc_index[%d] is already closed", index);
         ret = JGDI_ILLEGAL_STATE;
      } else {
         *outelem = elem;
      }
   } else {
       answer_list_add(alpp, "event has not a valid evc index", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
       ret = JGDI_ILLEGAL_STATE;
   }
   DRETURN(ret);

}
