TaskScheduler_stopWatching(TaskScheduler* scheduler)
{
  TaskListNode* iterator;
  TaskListNode* actualTask;
  Task* backup;
  struct timeval* tmp;
  int result;
  assert(scheduler != NULL);
  if (scheduler == NULL) {
    return 1;
  }
  tmp = TaskScheduler_get_actualTimer(scheduler);
  assert(tmp != NULL);
  if (tmp == NULL) {
    return 1;
  }
  if (timeval_subtract(&(scheduler->delta), tmp)) {
    return 1;
  }
  actualTask = scheduler->actualTask;
  assert(scheduler->actualTask != NULL);
  iterator = scheduler->head;
  while (iterator) {
    if (iterator != actualTask) {
      result = timeval_subtract(Task_get_timer(TaskListNode_get_task(iterator)), &(scheduler->delta));
      assert(result == 0);
    }
    if (timeval_lq_zero(Task_get_timer(TaskListNode_get_task(iterator)))) {
      Task_exec(TaskListNode_get_task(iterator));
      backup = TaskListNode_get_task(iterator);
      iterator = iterator->next;
      TaskScheduler_removeTask(scheduler, backup);
      continue;
    }
    iterator = iterator->next;
  }
  TaskScheduler_update(scheduler);
  return 0;
}
