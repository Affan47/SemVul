schedule_entry_compare (const struct schedule_entry *e1,
			const struct schedule_entry *e2)
{
  if (e1->tv.tv_sec < e2->tv.tv_sec)
    return -1;
  else if (e1->tv.tv_sec > e2->tv.tv_sec)
    return 1;
  else
    {
      if (e1->tv.tv_usec < e2->tv.tv_usec)
	return -1;
      else if (e1->tv.tv_usec > e2->tv.tv_usec)
	return 1;
      else
	{
	  if (e1->pri < e2->pri)
	    return -1;
	  else if (e1->pri > e2->pri)
	    return 1;
	  else
	    return 0;
	}
    }
}
