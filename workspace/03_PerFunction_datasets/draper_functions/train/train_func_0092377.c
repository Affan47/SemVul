_client_pause_fail(gearman_task_st *task)
{
  assert_msg(task->recv->command == GEARMAN_COMMAND_WORK_FAIL,
             "fail callback has been called out of order for task, or was registered to run on non-fail callback, see gearman_actions_t(3)");
  if (task->options.is_paused)
  {
    task->options.is_paused= false;
    return GEARMAN_SUCCESS;
  }
  task->options.is_paused= true;

  return GEARMAN_PAUSE;
}
