remove_from_reschedule_unknown_lists(sge_gdi_ctx_class_t *ctx,
                                     u_long32 job_number,
                                     u_long32 task_number)
{
   lListElem *host;

   DENTER(TOP_LAYER, "remove_from_reschedule_unknown_lists");

   for_each(host, *object_type_get_master_list(SGE_TYPE_EXECHOST)) {
      remove_from_reschedule_unknown_list(ctx, host, job_number, task_number);
   }

   DRETURN_VOID;
}
