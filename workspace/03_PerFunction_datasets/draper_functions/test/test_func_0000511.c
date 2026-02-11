tl_resume_timer(tl_timer * t)
{
    if (t->stopped) {
	t->stopped = 0;
	t->slowdown = tl_lookup_timer(t) - t->stoppedtime;
    }
}
