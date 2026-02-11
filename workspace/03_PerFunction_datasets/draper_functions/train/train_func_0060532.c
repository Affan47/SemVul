store_numeric_date(const char *datestr, struct tds_time *t)
{
	int TDS_MONTH = 0;
	int TDS_DAY = 0;
	int TDS_YEAR = 0;

	int state;
	char last_char = 0;
	const char *s;
	int month = 0, year = 0, mday = 0;


	if (strlen(datestr) == 10 && *(datestr + 4) == '-' && *(datestr + 7) == '-') {

		TDS_YEAR = 0;
		TDS_MONTH = 1;
		TDS_DAY = 2;
		state = TDS_YEAR;

	}

	else {
		TDS_MONTH = 0;
		TDS_DAY = 1;
		TDS_YEAR = 2;
		state = TDS_MONTH;
	}
	for (s = datestr; *s; s++) {
		if (!isdigit((unsigned char) *s) && isdigit((unsigned char) last_char)) {
			state++;
		} else {
			if (state == TDS_MONTH)
				month = (month * 10) + (*s - '0');
			if (state == TDS_DAY)
				mday = (mday * 10) + (*s - '0');
			if (state == TDS_YEAR)
				year = (year * 10) + (*s - '0');
		}
		last_char = *s;
	}

	if (month > 0 && month < 13)
		t->tm_mon = month - 1;
	else
		return 0;
	if (mday > 0 && mday < 32)
		t->tm_mday = mday;
	else
		return 0;

	return store_year(year, t);

}
