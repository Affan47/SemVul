nfprof_print(nfprof_t *profile_data, FILE *std) {
u_long usec, sec;
double fps, allsecs;

	usec = profile_data->used.ru_utime.tv_usec + profile_data->used.ru_stime.tv_usec;
	sec = profile_data->used.ru_utime.tv_sec + profile_data->used.ru_stime.tv_sec;

	if (usec > 1000000)
		usec -= 1000000, ++sec;


	allsecs = (double)sec + ((double)usec/1000000);
	if ( allsecs == 0.0 )
		fps = 0;
	else
		fps = (double)profile_data->numflows / ((double)sec + ((double)usec/1000000));

	fprintf(std, "Sys: %lu.%-3.3lus flows/second: %-10.1f ", sec, usec/1000, fps);

	if (profile_data->tend.tv_usec < profile_data->tstart.tv_usec)
		profile_data->tend.tv_usec += 1000000, --profile_data->tend.tv_sec;

	usec = profile_data->tend.tv_usec - profile_data->tstart.tv_usec;
	sec = profile_data->tend.tv_sec - profile_data->tstart.tv_sec;

	if ( usec == 0 && sec == 0 )

		fps = 0;
	else
		fps = (double)profile_data->numflows / ((double)sec + ((double)usec/1000000));

	fprintf(std, "Wall: %lu.%-3.3lus flows/second: %-10.1f\n", sec, usec/1000, fps);


}
