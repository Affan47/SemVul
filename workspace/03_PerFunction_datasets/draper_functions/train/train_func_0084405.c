xstrtoul(char *str, unsigned long use)
{
	char          *stop;
	unsigned long  line;

	line = strtoul(str, &stop, 10);

	if ((line < 0) || (*stop != 0)) line = use;

	return(line);
}
