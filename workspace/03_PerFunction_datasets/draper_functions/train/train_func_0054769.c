gearman_job_send_data(gearman_job_st *job, const void *data, size_t data_size)
{
  if (job)
  {
    const void *args[2];
    size_t args_size[2];

    if (job->reducer)
    {
      gearman_argument_t value= gearman_argument_make(NULL, 0, static_cast<const char *>(data), data_size);
      job->reducer->add(value);

      return GEARMAN_SUCCESS;
    }

    if ((job->options.work_in_use) == false)
    {
      args[0]= job->assigned.arg[0];
      args_size[0]= job->assigned.arg_size[0];
      args[1]= data;
      args_size[1]= data_size;
      gearman_return_t ret= gearman_packet_create_args(job->worker->universal, job->work,
                                                       GEARMAN_MAGIC_REQUEST,
                                                       GEARMAN_COMMAND_WORK_DATA,
                                                       args, args_size, 2);
      if (gearman_failed(ret))
      {
        return ret;
      }

      job->options.work_in_use= true;
    }

    return _job_send(job);
  }

  return GEARMAN_INVALID_ARGUMENT;
}
