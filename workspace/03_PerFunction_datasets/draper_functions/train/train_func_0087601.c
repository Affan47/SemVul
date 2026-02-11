qname(char *s)
{
	char *dot = strchr(s + 1, '.');

	if (dot)
	{
		*s = dot - (s + 1);
		qname(dot);
	}
	else
	{
		*s = strlen(s) - 1;
	}
}
