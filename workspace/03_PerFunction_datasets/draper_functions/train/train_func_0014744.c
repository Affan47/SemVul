gearman_job_build_reducer(gearman_job_st *job, gearman_aggregator_fn *aggregator_fn)
{
  if (job->reducer)
  {
    return true;
  }

  gearman_string_t reducer_func= gearman_job_reducer_string(job);

  job->reducer= new (std::nothrow) gearman_job_reducer_st(job->worker->universal, reducer_func, aggregator_fn);
  if (not job->reducer)
  {
    gearman_job_free(job);
    return false;
  }

  if (not job->reducer->init())
  {
    gearman_job_free(job);
    return false;
  }

  return true;
}
