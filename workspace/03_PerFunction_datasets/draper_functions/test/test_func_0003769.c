_g_time_val_cmp (GTimeVal *a,
		 GTimeVal *b)
{
	if (a->tv_sec == b->tv_sec) {
		if (a->tv_usec == b->tv_usec)
			return 0;
		else
			return a->tv_usec > b->tv_usec ? 1 : -1;
	}
	else if (a->tv_sec > b->tv_sec)
		return 1;
	else
		return -1;
}
