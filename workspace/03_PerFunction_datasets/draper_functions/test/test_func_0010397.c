setup_formatted_log_time(void)
{
	pg_time_t	stamp_time;
	char		msbuf[8];

	if (!saved_timeval_set)
	{
		gettimeofday(&saved_timeval, NULL);
		saved_timeval_set = true;
	}

	stamp_time = (pg_time_t) saved_timeval.tv_sec;


	pg_strftime(formatted_log_time, FORMATTED_TS_LEN,

				"%Y-%m-%d %H:%M:%S     %Z",
				pg_localtime(&stamp_time, log_timezone));


	sprintf(msbuf, ".%03d", (int) (saved_timeval.tv_usec / 1000));
	memcpy(formatted_log_time + 19, msbuf, 4);
}
