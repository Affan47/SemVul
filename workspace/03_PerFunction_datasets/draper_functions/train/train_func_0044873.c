set_global_timezone(const char *tzname)
{
	pg_tz	   *tznew;

	if (!tzname || !tzname[0])
		return false;

	tznew = pg_tzset(tzname);
	if (!tznew)
		return false;

	if (!tz_acceptable(tznew))
		return false;

	global_timezone = tznew;
	return true;
}
