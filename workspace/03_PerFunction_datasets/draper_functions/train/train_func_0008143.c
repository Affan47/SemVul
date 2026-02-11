calc_days(int m, int d, int year)
{
	int lp;

	lp = leap(year);
	if(year < 1)
		return 0L;
	if((m < 1) | (m > 12))
		return 0L;
	if((d < 1) | (d > month_length[lp][m]))
		return 0L;
	return year_to_days(--year) + days_in_months[lp][m] + d;
}
