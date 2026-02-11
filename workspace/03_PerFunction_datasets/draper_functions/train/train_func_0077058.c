print_job (job, format, state, job_index)
     JOB *job;
     int format, state, job_index;
{
  if (state == -1 || (JOB_STATE)state == job->state)
    pretty_print_job (job_index, format, stdout);
  return (0);
}
