gearman_execute(gearman_client_st *client,
                                 const char *function_name, size_t function_length,
                                 const char *unique_str, size_t unique_length,
                                 gearman_task_attr_t *task_attr,
                                 gearman_argument_t *arguments,
                                 void *context)
{
  if (client == NULL)
  {
    return NULL;
  }

  gearman_argument_t null_arg= gearman_argument_make(0, 0, 0, 0);
  if (arguments == NULL)
  {
    arguments= &null_arg;
  }

  if (function_name == NULL or function_length == 0)
  {
    gearman_error(client->universal, GEARMAN_INVALID_ARGUMENT, "function_name was NULL");
    return NULL;
  }
  gearman_string_t function= { function_name, function_length };

  gearman_task_st *task= NULL;
  gearman_unique_t unique= gearman_unique_make(unique_str, unique_length);
  if (task_attr)
  {
    switch (task_attr->kind)
    {
    case GEARMAN_TASK_ATTR_BACKGROUND:
      task= add_task(*client,
                     context,
                     pick_command_by_priority_background(task_attr->priority),
                     function,
                     unique,
                     arguments->value,
                     time_t(0),
                     gearman_actions_execute_defaults());
      break;

    case GEARMAN_TASK_ATTR_EPOCH:
      task= add_task(*client,
                     context,
                     GEARMAN_COMMAND_SUBMIT_JOB_EPOCH,
                     function,
                     unique,
                     arguments->value,
                     gearman_task_attr_has_epoch(task_attr),
                     gearman_actions_execute_defaults());
      break;

    case GEARMAN_TASK_ATTR_FOREGROUND:
      task= add_task(*client,
                     context,
                     pick_command_by_priority(task_attr->priority),
                     function,
                     unique,
                     arguments->value,
                     time_t(0),
                     gearman_actions_execute_defaults());
      break;
    }
  }
  else
  {
    task= add_task(*client,
                   NULL,
                   GEARMAN_COMMAND_SUBMIT_JOB,
                   function,
                   unique,
                   arguments->value,
                   time_t(0),
                   gearman_actions_execute_defaults());
  }

  if (task == NULL)
  {
    gearman_universal_error_code(client->universal);

    return NULL;
  }

  task->type= GEARMAN_TASK_KIND_EXECUTE;
  gearman_client_run_tasks(client);

  return task;
}
