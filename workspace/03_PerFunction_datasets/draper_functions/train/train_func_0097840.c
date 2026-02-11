my_timer(GB_TIMER *timer,bool on)
{
	if (timer->id) {
		MyTimerTag *tag = (MyTimerTag *)timer->tag;
		g_source_remove(timer->id);
		g_timer_destroy(tag->timer);
		g_free(tag);
		timer->id = 0;
		timer->tag = 0;
	}

	if (on)
	{
		MyTimerTag *tag = g_new(MyTimerTag, 1);
		tag->timer = g_timer_new();
		tag->timeout = timer->delay;
		timer->tag = (intptr_t)tag;
		timer->id = (intptr_t)g_timeout_add(timer->delay,(GSourceFunc)my_timer_function,(gpointer)timer);
		return;
	}
}
