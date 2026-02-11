DISGetTimestamp(dis_timestamp * result)
{

#if defined(NPSNET_COMPAT)
	time_t    i = time(0);

	result->time = i >> 1;
	result->type = i & 1;
#else
	struct timeval t;
	struct timezone tz;
	my_quad_t i;

	if (gettimeofday(&t, &tz) != 0) {
		return -1;
	}
	i = (t.tv_sec % 3600) * MILLION + t.tv_usec;
	i = (i * dis_timestamp_const / 3600) / MILLION;
	result->time = (unsigned int) i;
	result->type = 0;
#endif
	return 0;
}
