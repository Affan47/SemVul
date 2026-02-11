date_is_leap_year(short year)
{
	if (year < 0)
		year += 8001;

	if ((((year % 4) == 0) && ((year % 100) != 0)) || (year % 400) == 0)
		return 1;
	else
		return 0;
}
