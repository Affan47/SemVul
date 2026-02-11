figure_column(const char *w, int def)
{
	const char *ptr = strstr(w, "=");
	if (ptr == NULL)
		return def;
	double res;
	if (!getdnum(ptr + 1, &res))
		err("Cannot read column number in `\\", w, "'", "\\");
	return int(floor(res + 0.5));
}
