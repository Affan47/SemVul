_worker_allocate(gearman_worker_st *worker, bool is_clone)
{
  if (worker)
  {
    worker->options.allocated= false;
  }
  else
  {
    worker= new (std::nothrow) gearman_worker_st;
    if (worker == NULL)
    {
      return NULL;
    }

    worker->options.allocated= true;
  }

  worker->options.non_blocking= false;
  worker->options.packet_init= false;
  worker->options.change= false;
  worker->options.grab_uniq= true;
  worker->options.grab_all= true;
  worker->options.timeout_return= false;

  worker->state= GEARMAN_WORKER_STATE_START;
  worker->work_state= GEARMAN_WORKER_WORK_UNIVERSAL_GRAB_JOB;
  worker->function_count= 0;
  worker->job_count= 0;
  worker->work_result_size= 0;
  worker->context= NULL;
  worker->con= NULL;
  worker->job= NULL;
  worker->job_list= NULL;
  worker->function= NULL;
  worker->function_list= NULL;
  worker->work_function= NULL;
  worker->work_result= NULL;

  if (is_clone == false)
  {
    gearman_universal_initialize(worker->universal);
#if 0
    gearman_universal_set_timeout(worker->universal, GEARMAN_WORKER_WAIT_TIMEOUT);
#endif
  }

  if (setup_shutdown_pipe(worker->universal.wakeup_fd) == false)
  {
    if (worker->options.allocated)
    {
      delete worker;
    }

    return NULL;
  }

  return worker;
}
