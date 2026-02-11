add(char *p, char *type)
{
	while (*p)
		syntax[(signed char)*p++ + 130] = type;
}
