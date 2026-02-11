gearman_task_recv_data(gearman_task_st *task, void *data,
                                  size_t data_size,
                                  gearman_return_t *ret_ptr)
{
  gearman_return_t unused;
  if (ret_ptr == NULL)
  {
    ret_ptr= &unused;
  }

  if (task == NULL)
  {
    *ret_ptr= GEARMAN_INVALID_ARGUMENT;
    return 0;
  }

  return task->con->receive_data(data, data_size, *ret_ptr);
}
