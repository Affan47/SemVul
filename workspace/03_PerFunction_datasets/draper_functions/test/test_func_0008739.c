_der_gmtime(time_t t, struct tm *tm)
{
    time_t secday = t % (3600 * 24);
    time_t days = t / (3600 * 24);

    memset(tm, 0, sizeof(*tm));

    tm->tm_sec = secday % 60;
    tm->tm_min = (secday % 3600) / 60;
    tm->tm_hour = (int)(secday / 3600);


    if (days > (ASN1_MAX_YEAR * 365))
	return NULL;

    tm->tm_year = 70;
    while(1) {
	unsigned dayinyear = (is_leap(tm->tm_year) ? 366 : 365);
	if (days < dayinyear)
	    break;
	tm->tm_year += 1;
	days -= dayinyear;
    }
    tm->tm_mon = 0;

    while (1) {
	unsigned daysinmonth = ndays[is_leap(tm->tm_year)][tm->tm_mon];
	if (days < daysinmonth)
	    break;
	days -= daysinmonth;
	tm->tm_mon++;
    }
    tm->tm_mday = (int)(days + 1);

    return tm;
}
