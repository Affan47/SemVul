xxxqof_is_same_day (time_t ta, time_t tb)
{
	struct tm lta, ltb;
	lta = *localtime (&ta);
	ltb = *localtime (&tb);
	if (lta.tm_year == ltb.tm_year)
	{
	return (ltb.tm_yday - lta.tm_yday);
	}
	return (ltb.tm_year - lta.tm_year)*365;
}
