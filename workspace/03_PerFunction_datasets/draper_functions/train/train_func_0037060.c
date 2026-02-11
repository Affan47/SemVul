psWatchJob(JobID_t JobID)
{
   lnk_link_t *curr;

#  if DEBUG

      if (df == NULL)
         df = fopen("/tmp/pacct.out", "w");
      fprintf(df, "%d watching "F64"\n", get_gmt(), JobID);
      fflush(df);

#  endif


   if ((curr=find_job(JobID))) {
      LNK_DATA(curr, job_elem_t, link)->precreated = 0;
   } else {
      job_elem_t *job_elem = (job_elem_t *)malloc(sizeof(job_elem_t));
      memset(job_elem, 0, sizeof(job_elem_t));
      job_elem->starttime = get_gmt();
      job_elem->job.jd_jid = JobID;
      job_elem->job.jd_length = sizeof(psJob_t);
      LNK_INIT(&job_elem->procs);
      LNK_INIT(&job_elem->arses);

      LNK_ADD(job_list.prev, &job_elem->link);
   }

   return 0;
}
