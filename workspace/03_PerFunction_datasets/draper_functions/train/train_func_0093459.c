sge_set_job_cnts( sge_ref_t *ref,
                  int queued )
{
   int prj_job_cnt_nm = queued ? PR_pending_job_cnt : PR_job_cnt;
   int user_job_cnt_nm = queued ? UU_pending_job_cnt : UU_job_cnt;
   int us_job_cnt_nm = queued ? US_pending_job_cnt : US_job_cnt;
   if (ref->user) {
      lAddUlong(ref->user, user_job_cnt_nm, 1);
   }
   if (ref->project) {
      lAddUlong(ref->project, prj_job_cnt_nm, 1);
   }
   if (ref->dept) {
      lAddUlong(ref->dept, us_job_cnt_nm, 1);
   }

   return;
}
