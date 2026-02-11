compDate(struct tm *date1, struct tm *date2)
{

	if(date1->tm_year != date2->tm_year)
	{
		return (date1->tm_year < date2->tm_year) ? -1 : 1;
	}
	if(date1->tm_mon != date2->tm_mon)
	{
		return (date1->tm_mon < date2->tm_mon) ? -1 : 1;
	}
	if(date1->tm_mday != date2->tm_mday)
	{
		return (date1->tm_mday < date2->tm_mday) ? -1 : 1;
	}
	return 0;
}
