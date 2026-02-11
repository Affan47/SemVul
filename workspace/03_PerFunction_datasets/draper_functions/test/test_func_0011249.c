git_apply_config(const char *var, const char *value)
{
	if (!strcmp(var, "apply.whitespace")) {
		apply_default_whitespace = xstrdup(value);
		return 0;
	}
	return git_default_config(var, value);
}
