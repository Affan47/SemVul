gmtsub(const pg_time_t *timep, long offset, struct pg_tm * tmp)
{
	if (!gmt_is_set)
	{
		gmt_is_set = TRUE;
		gmtload(gmtptr);
	}
	timesub(timep, offset, gmtptr, tmp);


	if (offset != 0)
		tmp->tm_zone = wildabbr;
	else
		tmp->tm_zone = gmtptr->chars;
}
