DYNDNS_init(void)
{

  if(options & OPT_DAEMON)
  {
    if(!(max_interval > 0))
    {
      max_interval = DYNDNS_MAX_INTERVAL;
    }
  }
}
