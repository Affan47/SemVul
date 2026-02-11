timer_set_interval (unsigned int refnum, int interval)
{
    TIMER  *t = Pending_Timers;

    for (; t; t = t->next)
	if (t->refnum == refnum)
	{
	    t->interval = interval;
	    break;
	}
}
