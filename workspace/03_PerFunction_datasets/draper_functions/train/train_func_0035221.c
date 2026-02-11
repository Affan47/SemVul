get_pg_tz_for_zone(const char *tzname)
{
	pg_tz	   *tz;

	if (!tzname || !tzname[0])
		return NULL;

	tz = pg_tzset(tzname);
	if (!tz)
		return NULL;

	if (!tz_acceptable(tz))
		return NULL;

	return tz;
}
