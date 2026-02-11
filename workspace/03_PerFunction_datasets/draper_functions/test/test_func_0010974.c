initloggingplugin(struct loggingplugininfo &loggingplugininfo,
	class Options &options, bool debugmode)
{
	localdebugmode = debugmode;

	if (!debugmode) return false;

	loggingplugininfo.pluginname = PLUGIN_NAME;

	return true;
}
