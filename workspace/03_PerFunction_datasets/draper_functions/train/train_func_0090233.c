jgdi_get_evc_by_evid_and_lock(u_long32 evid, sge_evc_elem_t **elem, lList **alpp) {

   int i = 0;
   int evc_index = -1;

   DENTER(JGDI_LAYER, "jgdi_get_evc_by_evid_and_lock");

   *elem = NULL;

   for (i = 0; i < MAX_EVC_ARRAY_SIZE; i++) {
      sge_evc_elem_t *tmpelem = NULL;
      if (lockEVC("jgdi_get_evc_by_evid_and_lock", i, &tmpelem, alpp) == JGDI_SUCCESS) {
         if (tmpelem->sge_evc->ec_get_id(tmpelem->sge_evc) == evid) {
            *elem = tmpelem;
            evc_index = i;
            break;
         }
         unlockEVC("jgdi_get_evc_by_evid_and_lock", i);
      }
   }

   DRETURN(evc_index);
}
