ev_pending_count (EV_P)
{
  int pri;
  unsigned int count = 0;

  for (pri = NUMPRI; pri--; )
    count += pendingcnt [pri];

  return count;
}
