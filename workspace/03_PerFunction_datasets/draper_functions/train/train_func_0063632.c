v_n_get_current_time(uint32 *seconds, uint32 *fractions)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	if(seconds != NULL)
	    *seconds = tv.tv_sec;
	if(fractions != NULL)
		*fractions = tv.tv_usec * 1E-6 * (double) (uint32)~0;
}
