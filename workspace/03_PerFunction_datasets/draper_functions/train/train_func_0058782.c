timer_schedule (Timer_Callback timeout, Any_Type arg, Time delay)
{
  Timer_Queue *spoke;
  Timer *t, *p;
  u_long ticks;
  u_long delta;
  Time behind;

  if (timer_free_list)
    {
      t = timer_free_list;
      timer_free_list = t->q.next;
    }
  else
    {
      t = malloc (sizeof (*t));
      if (!t)
	{
	  fprintf (stderr, "%s.timer_schedule: %s\n",
		   prog_name, strerror (errno));
	  return 0;
	}
    }
  memset (t, 0, sizeof (*t));
  t->func = timeout;
  t->arg = arg;

  behind = (timer_now () - next_tick);
  if (behind > 0.0)
    delay += behind;

  if (delay < 0.0)
    ticks = 1;
  else
    {
      ticks = (delay + TIMER_INTERVAL / 2.0) * (1.0 / TIMER_INTERVAL);
      if (!ticks)
	ticks = 1;
    }

  spoke = curr + (ticks % WHEEL_SIZE);
  if (spoke >= wheel + WHEEL_SIZE)
    spoke -= WHEEL_SIZE;

  delta = ticks / WHEEL_SIZE;
  p = (Timer *) spoke;
  while (p->q.next && delta > p->q.next->delta)
    {
      delta -= p->q.next->delta;
      p = p->q.next;
    }
  t->q.next = p->q.next;
  t->q.prev = p;
  p->q.next = t;
  t->delta = delta;
  if (t->q.next)
    {
      t->q.next->q.prev = t;
      t->q.next->delta -= delta;
    }

  if (DBG > 2)
    fprintf (stderr, "timer_schedule: t=%p, delay=%gs, arg=%lx\n",
	     t, delay, arg.l);

  return t;
}
