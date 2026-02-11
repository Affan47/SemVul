sge_evc_destroy(sge_evc_t **sge_evc)
{
   DENTER(EVC_LAYER, "sge_evc_destroy");

   if (sge_evc == NULL || *sge_evc == NULL) {
      DRETURN_VOID;
   }


   pthread_mutex_lock(&((*sge_evc)->event_control.mutex));
   pthread_cond_broadcast(&((*sge_evc)->event_control.cond_var));
   pthread_mutex_unlock(&((*sge_evc)->event_control.mutex));

   pthread_cond_destroy(&((*sge_evc)->event_control.cond_var));
   pthread_mutex_destroy(&((*sge_evc)->event_control.mutex));
   lFreeList(&((*sge_evc)->event_control.new_events));

   lFreeElem(&((*sge_evc)->ec));
   FREE(*sge_evc);
   *sge_evc = NULL;

   DRETURN_VOID;
}
