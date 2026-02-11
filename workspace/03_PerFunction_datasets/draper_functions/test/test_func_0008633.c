isoweekdate2date(int isoweek, int wday, int *year, int *mon, int *mday)
{
	int			jday;

	jday = isoweek2j(*year, isoweek);

	if (wday > 1)
		jday += wday - 2;
	else
		jday += 6;
	j2date(jday, year, mon, mday);
}
