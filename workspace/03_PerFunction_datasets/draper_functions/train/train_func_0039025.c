tl_stop_timer(tl_timer * t)
{
    if (!t->stopped) {
	t->stoppedtime = tl_lookup_timer(t);
	t->stopped = 1;
    }
}
