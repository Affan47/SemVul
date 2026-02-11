git_default_push_config(const char *var, const char *value)
{
	if (!strcmp(var, "push.default")) {
		if (!value)
			return config_error_nonbool(var);
		else if (!strcmp(value, "nothing"))
			push_default = PUSH_DEFAULT_NOTHING;
		else if (!strcmp(value, "matching"))
			push_default = PUSH_DEFAULT_MATCHING;
		else if (!strcmp(value, "upstream"))
			push_default = PUSH_DEFAULT_UPSTREAM;
		else if (!strcmp(value, "tracking"))
			push_default = PUSH_DEFAULT_UPSTREAM;
		else if (!strcmp(value, "current"))
			push_default = PUSH_DEFAULT_CURRENT;
		else {
			error("Malformed value for %s: %s", var, value);
			return error("Must be one of nothing, matching, "
				     "tracking or current.");
		}
		return 0;
	}


	return 0;
}
