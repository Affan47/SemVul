date_to_timestamp(uint8_t *buff, uint32_t *timestamp)
{
	uint32_t year, month, day, hour, minute, second;
	uint32_t leap_day = 0;

	year   = 1000 * (buff[ 0] - '0') + 100 * (buff[ 1] - '0') +
	           10 * (buff[ 2] - '0') +       (buff[ 3] - '0');
	month  =   10 * (buff[ 4] - '0') +       (buff[ 5] - '0');
	day    =   10 * (buff[ 6] - '0') +       (buff[ 7] - '0');
	hour   =   10 * (buff[ 8] - '0') +       (buff[ 9] - '0');
	minute =   10 * (buff[10] - '0') +       (buff[11] - '0');
	second =   10 * (buff[12] - '0') +       (buff[13] - '0');

	if (year < 1970 || year > 2105 || month < 1 || month > 12 || day < 1) {
		return ZSCANNER_EBAD_DATE;
	} else {
		year -= 1970;
	}

	if (is_leap_year[year]) {
		if (month > 2) {
			leap_day = 1;
		} else if (month == 2 &&
		           day > (uint32_t)(days_in_months[month] + 1)) {
			return ZSCANNER_EBAD_DATE;
		}
	} else if (day > days_in_months[month]){
		return ZSCANNER_EBAD_DATE;
	}

	if (hour > 23 || minute > 59 || second > 59) {
		return ZSCANNER_EBAD_TIME;
	}

	*timestamp = hour * 3600 + minute * 60 + second +
	             (days_across_years[year] +
	             days_across_months[month] +
	             day - 1 + leap_day) * 86400;

	return ZSCANNER_OK;
}
