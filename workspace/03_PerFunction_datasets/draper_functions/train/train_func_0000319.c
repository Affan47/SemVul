my_timer_function(GB_TIMER *timer)
{
	if (timer->id)
	{
		GB.RaiseTimer(timer);

		if (timer->id)
		{
			MyTimerTag *tag = (MyTimerTag *)timer->tag;
			GTimer *t = tag->timer;
			int elapsed = (int)(g_timer_elapsed(t, NULL) * 1000) - tag->timeout;
			int next = timer->delay - elapsed;
			if (next < 10)
				next = 10;
			tag->timeout = next;
			g_timer_start(t);
			timer->id = (intptr_t)g_timeout_add(next, (GSourceFunc)my_timer_function,(gpointer)timer);

		}
	}

	return false;
}
