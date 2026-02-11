sge_ssi_job_cancel(sge_evc_class_t *evc, const char *job_identifier, bool reschedule)
{
   u_long32 job_id, ja_task_id;
   lList *ref_list = NULL, *alp;
   lListElem *ref_ep;
   char job_id_str[100];
   sge_gdi_ctx_class_t *ctx = evc->get_gdi_ctx(evc);

   DENTER(TOP_LAYER, "sge_ssi_job_cancel");


   if(reschedule) {
      DRETURN(false);
   }

   if(!parse_job_identifier(job_identifier, &job_id, &ja_task_id)) {
      DRETURN(false);
   }


   sprintf(job_id_str, sge_U32CFormat, sge_u32c(job_id));
   ref_ep = lAddElemStr(&ref_list, ID_str, job_id_str, ID_Type);
   ref_ep = lAddSubUlong(ref_ep, RN_min, ja_task_id, ID_ja_structure, RN_Type);
   lSetUlong(ref_ep, RN_max, ja_task_id);
   lSetUlong(ref_ep, RN_step, 1);


   alp = ctx->gdi(ctx, SGE_JB_LIST, SGE_GDI_DEL, &ref_list, NULL, NULL);

   answer_list_on_error_print_or_exit(&alp, stderr);

   DRETURN(true);
}
