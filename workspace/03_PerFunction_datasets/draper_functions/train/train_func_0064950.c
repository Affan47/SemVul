parsetime(const char **t)
{
unsigned h,m,s=0;

	if (!isdigit((int)(unsigned char)**t))	return (-1);
	h=parsedig(t);
	if (h > 23)		return (-1);
	if (**t != ':')		return (-1);
	++*t;
	if (!isdigit((int)(unsigned char)**t))	return (-1);
	m=parsedig(t);
	if (**t == ':')
	{
		++*t;
		if (!isdigit((int)(unsigned char)**t))	return (-1);
		s=parsedig(t);
	}
	if (m > 59 || s > 59)	return (-1);
	return (h * 60 * 60 + m * 60 + s);
}
