GNUNET_SCHEDULER_get_load (enum GNUNET_SCHEDULER_Priority p)
{
  struct Task *pos;
  unsigned int ret;

  GNUNET_assert (active_task != NULL);
  if (p == GNUNET_SCHEDULER_PRIORITY_COUNT)
    return ready_count;
  if (p == GNUNET_SCHEDULER_PRIORITY_KEEP)
    p = current_priority;
  ret = 0;
  pos = ready[check_priority (p)];
  while (pos != NULL)
  {
    pos = pos->next;
    ret++;
  }
  return ret;
}
