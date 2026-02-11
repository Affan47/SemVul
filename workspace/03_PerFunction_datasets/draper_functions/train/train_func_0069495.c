git_config_bool_or_int(const char *name, const char *value, int *is_bool)
{
	*is_bool = 1;
	if (!value)
		return 1;
	if (!*value)
		return 0;
	if (!strcasecmp(value, "true") || !strcasecmp(value, "yes"))
		return 1;
	if (!strcasecmp(value, "false") || !strcasecmp(value, "no"))
		return 0;
	*is_bool = 0;
	return git_config_int(name, value);
}
