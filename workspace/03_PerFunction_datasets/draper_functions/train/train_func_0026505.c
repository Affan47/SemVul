p_str(struct lib_context *lc, char **string, const char *s)
{
	int ret;

	if ((ret = grow_string(lc, string, s)))
		strcat(*string, s);

	return ret;
}
