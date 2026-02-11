monitor_helper_locate(char *default_path)
{
	char *helper_path;

	debug(D_RMON,"locating helper library...\n");

	debug(D_RMON,"trying library from $%s.\n", RESOURCE_MONITOR_HELPER_ENV_VAR);
	helper_path = getenv(RESOURCE_MONITOR_HELPER_ENV_VAR);
	if(helper_path)
	{
		if(access(helper_path, R_OK|X_OK) == 0)
			return xxstrdup(helper_path);
	}

	if(default_path)
	{
		debug(D_RMON,"trying library at default path...\n");
		if(access(default_path, R_OK|X_OK) == 0)
			return xxstrdup(default_path);
	}

	debug(D_RMON,"trying library at default location.\n");
	free(helper_path);
	helper_path = string_format("%s/lib/librmonitor_helper.so", INSTALL_PATH);
	if(access(helper_path, R_OK|X_OK) == 0)
		return helper_path;

	return NULL;
}
