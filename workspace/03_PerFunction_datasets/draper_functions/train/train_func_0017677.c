__pthread_current_priority (void)
{
  struct pthread *self = THREAD_SELF;
  if ((self->flags & (ATTR_FLAG_POLICY_SET | ATTR_FLAG_SCHED_SET))
      == (ATTR_FLAG_POLICY_SET | ATTR_FLAG_SCHED_SET))
    return self->schedparam.sched_priority;

  int result = 0;

  lll_lock (self->lock, LLL_PRIVATE);

  if ((self->flags & ATTR_FLAG_SCHED_SET) == 0)
    {
      if (__sched_getparam (self->tid, &self->schedparam) != 0)
	result = -1;
      else
	self->flags |= ATTR_FLAG_SCHED_SET;
    }

  if ((self->flags & ATTR_FLAG_POLICY_SET) == 0)
    {
      self->schedpolicy = __sched_getscheduler (self->tid);
      if (self->schedpolicy == -1)
	result = -1;
      else
	self->flags |= ATTR_FLAG_POLICY_SET;
    }

  if (result != -1)
    result = self->schedparam.sched_priority;

  lll_unlock (self->lock, LLL_PRIVATE);

  return result;
}
