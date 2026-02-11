imap_read_date(const char *cp)
{
	time_t	t;
	int	year, month, day, i, tzdiff;
	struct tm	*tmptr;
	char	*xp, *yp;

	if (*cp == '"')
		cp++;
	day = strtol(cp, &xp, 10);
	if (day <= 0 || day > 31 || *xp++ != '-')
		return -1;
	for (i = 0; month_names[i]; i++)
		if (ascncasecmp(xp, month_names[i], 3) == 0)
			break;
	if (month_names[i] == NULL)
		return -1;
	month = i+1;
	if (xp[3] != '-')
		return -1;
	year = strtol(&xp[4], &yp, 10);
	if (year < 1970 || year > 2037 || yp != &xp[8])
		return -1;
	if (yp[0] != '\0' && (yp[1] != '"' || yp[2] != '\0'))
		return -1;
	if ((t = combinetime(year, month, day, 0, 0, 0)) == (time_t)-1)
		return -1;
	tzdiff = t - mktime(gmtime(&t));
	tmptr = localtime(&t);
	if (tmptr->tm_isdst > 0)
		tzdiff += 3600;
	t -= tzdiff;
	return t;
}
