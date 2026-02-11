mono_100ns_datetime (void)
{
	struct timeval tv;
	if (gettimeofday (&tv, NULL) == 0)
		return (((gint64)tv.tv_sec + EPOCH_ADJUST) * 1000000 + tv.tv_usec) * 10;
	return 0;
}
