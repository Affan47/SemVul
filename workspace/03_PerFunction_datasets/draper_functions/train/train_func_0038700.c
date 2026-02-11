reloadLib(const char *cfgPath)
{
	int ret;
	freeKnownChips();
	ret = loadConfig(cfgPath, 1);
	if (!ret)
		ret = initKnownChips();
	return ret;
}
