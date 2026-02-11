write_textual_restarts(int curr, int use_tm_start, int use_tm_end, int tab,
			    struct tm *rectime, struct tm *loctime)
{
	char cur_date[32], cur_time[32];


	sadf_get_record_timestamp_struct(curr, rectime, loctime);


	if ((use_tm_start && (datecmp(loctime, &tm_start) < 0)) ||
	    (use_tm_end && (datecmp(loctime, &tm_end) > 0)))
		return;

	set_record_timestamp_string(curr, cur_date, cur_time, 32, rectime);

	if (*fmt[f_position]->f_restart) {
		(*fmt[f_position]->f_restart)(&tab, F_MAIN, cur_date, cur_time,
					      !PRINT_LOCAL_TIME(flags) &&
					      !PRINT_TRUE_TIME(flags), &file_hdr);
	}
}
