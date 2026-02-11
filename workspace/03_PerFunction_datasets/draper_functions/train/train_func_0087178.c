startWorkerTask (Capability *cap)
{
  int r;
  OSThreadId tid;
  Task *task;


  task = newTask(rtsTrue);


  ACQUIRE_LOCK(&task->lock);

  task->cap = cap;


  ASSERT_LOCK_HELD(&cap->lock);
  cap->running_task = task;

  r = createOSThread(&tid, (OSThreadProc*)workerStart, task);
  if (r != 0) {
    sysErrorBelch("failed to create OS thread");
    stg_exit(EXIT_FAILURE);
  }

  debugTrace(DEBUG_sched, "new worker task (taskCount: %d)", taskCount);

  task->id = tid;


  RELEASE_LOCK(&task->lock);
}
