gfarm_timespec_normalize(struct gfarm_timespec *t)
{
	long n;

	if (t->tv_nsec >= GFARM_SECOND_BY_NANOSEC) {
		n = t->tv_nsec / GFARM_SECOND_BY_NANOSEC;
		t->tv_nsec -= n * GFARM_SECOND_BY_NANOSEC;
		t->tv_sec += n;
	} else if (t->tv_nsec < 0) {
		n = -t->tv_nsec / GFARM_SECOND_BY_NANOSEC + 1;
		t->tv_nsec += n * GFARM_SECOND_BY_NANOSEC;
		t->tv_sec -= n;
	}
}
