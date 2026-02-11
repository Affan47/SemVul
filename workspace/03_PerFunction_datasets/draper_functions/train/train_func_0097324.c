GNUNET_SCHEDULER_add_delayed_with_priority (struct GNUNET_TIME_Relative delay,
					    enum GNUNET_SCHEDULER_Priority priority,
					    GNUNET_SCHEDULER_Task task, void *task_cls)
{
  struct Task *t;
  struct Task *pos;
  struct Task *prev;

#if EXECINFO
  void *backtrace_array[MAX_TRACE_DEPTH];
#endif

  GNUNET_assert (active_task != NULL);
  GNUNET_assert (NULL != task);
  t = GNUNET_malloc (sizeof (struct Task));
  t->callback = task;
  t->callback_cls = task_cls;
#if EXECINFO
  t->num_backtrace_strings = backtrace (backtrace_array, MAX_TRACE_DEPTH);
  t->backtrace_strings =
      backtrace_symbols (backtrace_array, t->num_backtrace_strings);
#endif
  t->read_fd = -1;
  t->write_fd = -1;
  t->id = ++last_id;
#if PROFILE_DELAYS
  t->start_time = GNUNET_TIME_absolute_get ();
#endif
  t->timeout = GNUNET_TIME_relative_to_absolute (delay);
  t->priority = priority;
  t->lifeness = current_lifeness;


  prev = pending_timeout_last;
  if (prev != NULL)
  {
    if (prev->timeout.abs_value > t->timeout.abs_value)
      prev = NULL;
    else
      pos = prev->next;
  }
  if (prev == NULL)
  {

    pos = pending_timeout;
  }
  while ((pos != NULL) &&
         ((pos->timeout.abs_value <= t->timeout.abs_value) ||
          (pos->reason != 0)))
  {
    prev = pos;
    pos = pos->next;
  }
  if (prev == NULL)
    pending_timeout = t;
  else
    prev->next = t;
  t->next = pos;

  pending_timeout_last = t;

  LOG (GNUNET_ERROR_TYPE_DEBUG, "Adding task: %llu / %p\n", t->id,
       t->callback_cls);
#if EXECINFO
  int i;

  for (i = 0; i < t->num_backtrace_strings; i++)
    LOG (GNUNET_ERROR_TYPE_DEBUG, "Task %llu trace %d: %s\n", t->id, i,
         t->backtrace_strings[i]);
#endif
  return t->id;
}
