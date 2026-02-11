compute_soft_violations(const sge_assignment_t *a, lListElem *queue, int violation, lList *load_attr, lList *config_attr,
                    lList *actual_attr, u_long32 layer, double lc_factor, u_long32 tag)
{
   u_long32 job_id;
   const char *queue_name = NULL;
   dstring reason;
   char reason_buf[1024 + 1];
   unsigned int soft_violation = violation;
   lList *soft_requests = NULL;
   lListElem *attr;
   u_long32 start_time = DISPATCH_TIME_NOW;

   DENTER(TOP_LAYER, "compute_soft_violations");

   sge_dstring_init(&reason, reason_buf, sizeof(reason_buf));

   soft_requests = lGetList(a->job, JB_soft_resource_list);
   clear_resource_tags(soft_requests, tag);

   job_id = a->job_id;
   if (queue) {
      queue_name = lGetString(queue, QU_full_name);
   }


   for_each(attr, soft_requests) {
      switch (ri_time_by_slots(a, attr, load_attr, config_attr, actual_attr, queue,
                      &reason, false, 1, layer, lc_factor, &start_time, queue_name?queue_name:"no queue")) {

            case DISPATCH_NEVER_CAT:
               soft_violation++;
               break;

            case DISPATCH_MISSING_ATTR:
            case DISPATCH_NOT_AT_TIME:
               if (tag == QUEUE_TAG && lGetUlong(attr, CE_tagged) == NO_TAG) {
                  soft_violation++;
               }
               break;

            default:
               if (lGetUlong(attr, CE_tagged) < tag)
                  lSetUlong(attr, CE_tagged, tag);
      }
   }

   if (queue) {
      DPRINTF(("queue %s does not fulfill soft %d requests (first: %s)\n",
         queue_name, soft_violation, reason_buf));


      if (lGetList(a->job, JB_soft_queue_list)) {
         lList *qref_list = lGetList(a->job, JB_soft_queue_list);
         lListElem *qr;
         const char *qinstance_name = NULL;

         qinstance_name = lGetString(queue, QU_full_name);

         for_each (qr, qref_list) {
            if (qref_cq_rejected(lGetString(qr, QR_name), lGetString(queue, QU_qname),
                lGetHost(queue, QU_qhostname), a->hgrp_list)) {
               DPRINTF(("Queue \"%s\" is not contained in the soft "
                        "queue list (-q) that was requested by job %d\n",
                        qinstance_name, (int) job_id));
               soft_violation++;
            }
         }
      }


      lSetUlong(queue, QU_soft_violation, soft_violation);
   }

   DRETURN(soft_violation);
}
