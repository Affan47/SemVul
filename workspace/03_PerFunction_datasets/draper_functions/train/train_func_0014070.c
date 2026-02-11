dev_poll_remain_ms(void)
{
	int msecs;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	msecs = (next_dev_poll_time.tv_sec - tv.tv_sec) * 1000;
	msecs += (next_dev_poll_time.tv_usec - tv.tv_usec) / 1000;
	if(msecs < 0)
		return 0;
	return msecs;
}
