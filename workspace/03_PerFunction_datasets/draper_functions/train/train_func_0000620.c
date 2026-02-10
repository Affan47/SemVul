findMeter(char *s)
{
	int i = 1;

	while (strcmp(meters[i], " "))
		if (!strcasecmp(s, (char *) meters[i]))
			return(i);
		else
			i++;
	return LX_ERROR_BYTE;
}
