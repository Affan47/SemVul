updateMechList(void)
{
	gss_mech_info minfo;

#if defined(_WIN32)
	time_t lastConfModTime = getRegConfigModTime(MECH_KEY);
	if (g_confFileModTime >= lastConfModTime)
		return;
	g_confFileModTime = lastConfModTime;
	loadConfigFromRegistry(HKEY_CURRENT_USER, MECH_KEY);
	loadConfigFromRegistry(HKEY_LOCAL_MACHINE, MECH_KEY);
#else
	char *fileName;
	struct stat fileInfo;

	fileName = MECH_CONF;


	if (stat(fileName, &fileInfo) != 0 ||
	    g_confFileModTime >= fileInfo.st_mtime)
		return;
	g_confFileModTime = fileInfo.st_mtime;
	loadConfigFile(fileName);
#endif


	for (minfo = g_mechList; minfo != NULL; minfo = minfo->next) {
		if (minfo->is_interposer && minfo->mech == NULL)
			loadInterMech(minfo);
	}
}
