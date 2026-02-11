set_var(char *line, int *var)
{
	char *s;

	if (!(s = strchr(line, '='))) {
		IBWARN("bad assignment: missing '=' sign");
		return -1;
	}

	*var = strtol(s + 1, 0, 0);
	return 1;
}
