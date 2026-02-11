enableCursor(bool enable)
{
	static u32 interval = 500;
	static bool inited = false;
	if (!inited) {
		inited = true;
		Config::instance()->getOption("cursor-interval", interval);
	}

	if (!interval) return;

	static bool enabled = false;
	if (enabled == enable) return;
	enabled = enable;

	u32 val = (enable ? interval : 0);
	u32 sec = val / 1000, usec = (val % 1000) * 1000;

	struct itimerval timer;
	timer.it_interval.tv_usec = usec;
	timer.it_interval.tv_sec = sec;
	timer.it_value.tv_usec = usec;
	timer.it_value.tv_sec = sec;

	setitimer(ITIMER_REAL, &timer, NULL);
}
