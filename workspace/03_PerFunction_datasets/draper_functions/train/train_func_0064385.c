japi_get_job(u_long32 jobid, lList **retrieved_job_list, dstring *diag)
{
   lList *mal = NULL;
   lList *alp = NULL;
   lListElem *aep = NULL;
   int jb_id = 0;
   state_gdi_multi state = STATE_GDI_MULTI_INIT;
   lCondition *job_selection = NULL;
   lEnumeration *job_fields = NULL;
   u_long32 quality = 0;

   DENTER(TOP_LAYER, "japi_get_job");


   job_selection = lWhere("%T(%I==%u)", JB_Type, JB_job_number, jobid);
   job_fields = lWhat("%T(%I%I%I%I%I%I%I%I%I%I%I)", JB_Type,
         JB_job_number,
         JB_type,
         JB_ja_structure,
         JB_ja_n_h_ids,
         JB_ja_u_h_ids,
         JB_ja_s_h_ids,
         JB_ja_o_h_ids,
         JB_ja_a_h_ids,
         JB_ja_tasks,
         JB_jid_predecessor_list,
         JB_execution_time);

   if (!job_selection || !job_fields) {
      japi_standard_error(DRMAA_ERRNO_NO_MEMORY, diag);
      DRETURN(DRMAA_ERRNO_NO_MEMORY);
   }

   jb_id = ctx->gdi_multi(ctx, &alp, SGE_GDI_SEND, SGE_JB_LIST, SGE_GDI_GET, NULL,
                          job_selection, job_fields, &state, true);
   ctx->gdi_wait(ctx, &alp, &mal, &state);
   lFreeWhere(&job_selection);
   lFreeWhat(&job_fields);

   sge_gdi_extract_answer(&alp, SGE_GDI_GET, SGE_JB_LIST, jb_id, mal, retrieved_job_list);
   lFreeList(&mal);
   aep = lFirst(alp);

   if (aep == NULL) {
      sge_dstring_copy_string(diag, MSG_JAPI_BAD_GDI_ANSWER_LIST);
      DRETURN(DRMAA_ERRNO_INTERNAL_ERROR);
   }

   quality = lGetUlong(aep, AN_quality);

   if (quality == ANSWER_QUALITY_ERROR) {
      answer_to_dstring(aep, diag);
      lFreeList(&alp);
      DRETURN(DRMAA_ERRNO_DRM_COMMUNICATION_FAILURE);
   }

   lFreeList(&alp);

   DRETURN(DRMAA_ERRNO_SUCCESS);
}
