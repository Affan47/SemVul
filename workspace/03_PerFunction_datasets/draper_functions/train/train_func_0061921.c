PluginExists(const char * PluginPath)
{


	if (access(PluginPath, R_OK) != 0) {
		if (DEBUGPLUGIN) {
			PILLog(PIL_DEBUG, "Plugin file %s does not exist"
			,	PluginPath);
		}
		return PIL_NOPLUGIN;
	}
	return PIL_OK;
}
