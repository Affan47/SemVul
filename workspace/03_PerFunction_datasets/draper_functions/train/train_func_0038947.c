trace_jr()
{
   lListElem *jr;

   DENTER(TOP_LAYER, "trace_jr");

   DPRINTF(("--- JOB REPORT LIST ----------------\n"));
   for_each (jr, jr_list) {
      const char *s;

      if ((s=lGetString(jr, JR_pe_task_id_str))) {
         DPRINTF(("Jobtask "sge_u32"."sge_u32" task %s\n", lGetUlong(jr, JR_job_number), lGetUlong(jr, JR_ja_task_number), s));
      } else {
         DPRINTF(("Jobtask "sge_u32"."sge_u32"\n", lGetUlong(jr, JR_job_number), lGetUlong(jr, JR_ja_task_number)));
      }
   }
   DEXIT;
}
