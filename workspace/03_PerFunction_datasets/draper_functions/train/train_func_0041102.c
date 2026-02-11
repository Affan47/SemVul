gc_config(const char *var, const char *value)
{
	if (!strcmp(var, "gc.packrefs")) {
		if (!strcmp(value, "notbare"))
			pack_refs = -1;
		else
			pack_refs = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "gc.aggressivewindow")) {
		aggressive_window = git_config_int(var, value);
		return 0;
	}
	return git_default_config(var, value);
}
