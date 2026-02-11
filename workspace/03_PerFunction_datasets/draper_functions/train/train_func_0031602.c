crash_time_iso(char *buf, size_t size)
{
	const size_t num_reserved = 1;
	struct tm tm;
	cursor_t cursor;


	if (size < num_reserved)
		return;

	cursor.buf = buf;
	cursor.size = size - num_reserved;

	if (!off_time(time(NULL) + vars->gmtoff, 0, &tm)) {
		buf[0] = '\0';
		return;
	}

	crash_append_fmt_u(&cursor, TM_YEAR_ORIGIN + tm.tm_year);
	crash_append_fmt_c(&cursor, '-');
	crash_append_fmt_02u(&cursor, tm.tm_mon + 1);
	crash_append_fmt_c(&cursor, '-');
	crash_append_fmt_02u(&cursor, tm.tm_mday);
	crash_append_fmt_c(&cursor, ' ');
	crash_append_fmt_02u(&cursor, tm.tm_hour);
	crash_append_fmt_c(&cursor, ':');
	crash_append_fmt_02u(&cursor, tm.tm_min);
	crash_append_fmt_c(&cursor, ':');
	crash_append_fmt_02u(&cursor, tm.tm_sec);

	cursor.size += num_reserved;
	crash_append_fmt_c(&cursor, '\0');
}
