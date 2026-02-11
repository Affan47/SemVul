gearman_job_unique(const gearman_job_st *job)
{
  if (job)
  {
    if (job->assigned.command == GEARMAN_COMMAND_JOB_ASSIGN_UNIQ or
        job->assigned.command == GEARMAN_COMMAND_JOB_ASSIGN_ALL)
    {
      return static_cast<const char *>(job->assigned.arg[2]);
    }

    return "";
  }

  return NULL;
}
