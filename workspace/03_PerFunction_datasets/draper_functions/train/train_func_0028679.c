_ipmi_kcs_timeval_diff (struct timeval *start, struct timeval *end)
{
  unsigned long t;

  assert (start);
  assert (end);

  if (end->tv_sec == start->tv_sec)
    t = end->tv_usec - start->tv_usec;
  else
    {
      t = (end->tv_sec - start->tv_sec - 1) * IPMI_KCS_MICROSECONDS_IN_SECOND;
      t += (IPMI_KCS_MICROSECONDS_IN_SECOND - start->tv_usec);
      t += end->tv_usec;
    }

  return (t);
}
