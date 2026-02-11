b_vformat_time_to_unix(const char *inptime)
{
	char *date = NULL;
	char *time = NULL;
	char *ftime = NULL;
	if ((ftime = g_strrstr(inptime, "T"))) {

		date = g_strndup(inptime, ftime - inptime);
		if (ftime[3] == ':')
			time = g_strndup(ftime + 1, 8);
		else
			time = g_strndup(ftime + 1, 6);
	} else {
		date = g_strdup(inptime);
	}

	struct tm btime;
	memset(&btime, 0, sizeof(struct tm));
	btime.tm_isdst = -1;

	if (strlen(date) == 10) {
		btime.tm_year = date[0] * 1000 + date[1] * 100 + date[2] * 10 + date[3] - '0' * 1111 - 1900;
		btime.tm_mon = date[5] * 10 + date[6] - '0' * 11 - 1;
		btime.tm_mday = date[8] * 10 + date[9] - '0' * 11;
	} else {
		btime.tm_year = date[0] * 1000 + date[1] * 100 + date[2] * 10 + date[3] - '0' * 1111- 1900;
		btime.tm_mon = date[4] * 10 + date[5] - '0' * 11 - 1;
		btime.tm_mday = date[6] * 10 + date[7] - '0' * 11;
	}

	if (time && strlen(time) == 8) {

		btime.tm_hour = time[0] * 10 + time[1] - '0' * 11;
		btime.tm_min = time[3] * 10 + time[4] - '0' * 11;
		btime.tm_sec = time[6] * 10 + time[7] - '0' * 11;
	} else if (time && strlen(time) == 6) {
		btime.tm_hour = time[0] * 10 + time[1] - '0' * 11;
		btime.tm_min = time[2] * 10 + time[3] - '0' * 11;
		btime.tm_sec = time[4] * 10 + time[5] - '0' * 11;
	}

	time_t utime = mktime(&btime);
	return utime;
}
