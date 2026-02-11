rudp_create(void)
{
	rudp_t *rudp;
	struct timeval now[1];

	if (gettimeofday(now, NULL) == -1)
		return NULL;

	if (!(rudp = mem_new(rudp_t)))
		return NULL;

	rudp->base = now->tv_sec;
	rudp_init(rudp);

	return rudp;
}
