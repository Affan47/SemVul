clock_gettime_ns(clockid_t clk)
{
	int ret;
	struct timespec time;

	ret = clock_gettime(clk, &time);
	if (ret < 0)
	{
		pr_error_info("clock_gettime");
		return ret;
	}

	return (u64) time.tv_sec * 1000 * 1000 * 1000 + time.tv_nsec;
}
