select_task(void)
{
  const struct task *task;

  for (task = process->tasks; task->ready != NULL; ++task) {
    if (task->ready()) {
      next_task = task;
      return;
    }
  }

  next_task = NULL;
}
