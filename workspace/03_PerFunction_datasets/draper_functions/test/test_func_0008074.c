git_config_get_string(const char **out, const git_config *cfg, const char *name)
{
	int ret;
	const char *str = NULL;

	if ((ret = get_string(&str, cfg, name)) < 0)
		return ret;

	*out = str == NULL ? "" : str;
	return 0;
}
