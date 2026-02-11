time_parse_minutes(const char *s)
{
	unsigned int hour, minute, second = 0;
	char *e;

	hour = strtoul(s, &e, 10);
	if (*e != ':' || hour > 23)
		goto out;

	s = e + 1;
	minute = strtoul(s, &e, 10);
	if ((*e != ':' && *e != '\0') || minute > 59)
		goto out;
	if (*e == '\0')
		goto eval;

	s = e + 1;
	second = strtoul(s, &e, 10);
	if (*e != '\0' || second > 59)
		goto out;

 eval:
	return 60 * 60 * hour + 60 * minute + second;

 out:
	xtables_error(PARAMETER_PROBLEM, "invalid time \"%s\" specified, "
	           "should be hh:mm[:ss] format and within the boundaries", s);
	return -1;
}
