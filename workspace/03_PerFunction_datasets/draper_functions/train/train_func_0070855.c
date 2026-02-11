do_job_slave(sge_gdi_ctx_class_t *ctx, struct_msg_t *aMsg)
{
   int ret = 1;
   lListElem *jelem, *ja_task;
   u_long32 feature_set;
   lList *answer_list = NULL;

   DENTER(TOP_LAYER, "do_job_slave");


   if (unpackint(&(aMsg->buf), &feature_set)) {
      ERROR((SGE_EVENT, MSG_COM_UNPACKFEATURESET));
      DRETURN(0);
   }


   if (!object_unpack_elem_verify(&answer_list, &(aMsg->buf), &jelem, JB_Type)) {
      answer_list_output(&answer_list);
      ERROR((SGE_EVENT, MSG_COM_UNPACKJOB));
      DRETURN(0);
   }
   lFreeList(&answer_list);

   for_each(ja_task, lGetList(jelem, JB_ja_tasks)) {
      DPRINTF(("Job: %ld Task: %ld\n", (long) lGetUlong(jelem, JB_job_number),
         (long) lGetUlong(ja_task, JAT_task_number)));
      ret = handle_job(ctx, jelem, ja_task, 1);
   }

   if (ret)  {
      lFreeElem(&jelem);
   }

   DRETURN(0);
}
