client_do_background(gearman_client_st *client,
                                      gearman_command_t command,
                                      gearman_string_t &function,
                                      gearman_unique_t &unique,
                                      gearman_string_t &workload,
                                      gearman_job_handle_t job_handle)
{
  if (client == NULL)
  {
    return GEARMAN_INVALID_ARGUMENT;
  }

  gearman_task_st do_task;
  gearman_task_st *do_task_ptr= add_task(*client, &do_task,
                                         client,
                                         command,
                                         function,
                                         unique,
                                         workload,
                                         time_t(0),
                                         gearman_actions_do_default());
  if (do_task_ptr == NULL)
  {
    return gearman_universal_error_code(client->universal);
  }

  gearman_task_clear_fn(do_task_ptr);

  gearman_return_t ret= gearman_client_run_block_tasks(client, do_task_ptr);
  assert(ret != GEARMAN_IO_WAIT);
  if (ret != GEARMAN_IO_WAIT)
  {
    if (job_handle)
    {
      strncpy(job_handle, do_task.job_handle, GEARMAN_JOB_HANDLE_SIZE);
    }
    client->new_tasks= 0;
    client->running_tasks= 0;
  }
  gearman_task_free(&do_task);

  return ret;
}
