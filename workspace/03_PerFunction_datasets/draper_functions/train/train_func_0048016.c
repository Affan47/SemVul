calculate_pending_shared_override_tickets(sge_ref_t *job_ref, int num_jobs, int dependent) {
         lList *fcategories = NULL;
         sge_ref_list_t *ref_array = NULL;
         sge_ref_t **sort_list=NULL;
         int i;
         u_long32 max;
         u_long32 job_ndx;

         DENTER(TOP_LAYER, "calculate_pending_shared_override_tickets");

         max = build_functional_categories(job_ref, num_jobs, &fcategories, &ref_array, dependent,
                                     JB_override_tickets, UU_oticket, PR_oticket, US_oticket);

         if (max > 0) {
            sort_list = malloc(max * sizeof(sge_ref_t *));

            if (sort_list == NULL) {


               FREE(sort_list);

               if (fcategories != NULL) {
                  free_fcategories(&fcategories, &ref_array);
               }
               DEXIT;
               return;
            }

            for(i=0; i < max; i++) {
               double max_otickets=-1;
               u_long32 jid, tid, max_jid=0, max_tid=0;

               lListElem *current = NULL;
               lListElem *max_current = NULL;

               for_each(current, fcategories){
                  sge_ref_list_t *tmp = (lGetRef(current, FCAT_jobrelated_ticket_first));
                  sge_ref_t *jref = tmp->ref;
                  double otickets;

                  otickets = calc_pjob_override_tickets_shared(jref);
                  jid = lGetUlong(jref->job, JB_job_number);
                  tid = REF_GET_JA_TASK_NUMBER(jref);


                  if ((max_otickets < otickets) ||
                      (max_current == NULL)) {
                     max_current = current;
                     max_otickets = otickets;
                     max_jid = jid;
                     max_tid = tid;
                     sort_list[i] = jref;
                  }
                  else if (max_otickets == otickets) {
                     if ((max_jid > jid) ||
                        ((max_jid == jid) && (max_tid > tid))) {
                           max_current = current;
                           max_otickets = otickets;
                           max_jid = jid;
                           max_tid = tid;
                           sort_list[i] = jref;
                     }
                  }
               }

               if (max_current != NULL) {
                  sge_ref_list_t *tmp =lGetRef(max_current, FCAT_jobrelated_ticket_first);
                  sge_set_job_cnts(tmp->ref, 0);
                  lSetRef(max_current, FCAT_jobrelated_ticket_first, tmp->next);
                  sort_list[i]->tickets += max_otickets;


                  if(lGetRef(max_current, FCAT_jobrelated_ticket_first) == NULL){
                     lSetRef(max_current, FCAT_jobrelated_ticket_last,  NULL);
                     lSetRef(current, FCAT_user, NULL);
                     lSetRef(current, FCAT_dept, NULL);
                     lSetRef(current, FCAT_project, NULL);

                     lRemoveElem(fcategories, &max_current);
                  }
               }
               else {
                  break;
               }
            }


            for(job_ndx=0; job_ndx < max; job_ndx++) {
               sge_unset_job_cnts(sort_list[job_ndx], 0);
            }
            FREE(sort_list);
         }


         free_fcategories(&fcategories, &ref_array);

   return;
}
