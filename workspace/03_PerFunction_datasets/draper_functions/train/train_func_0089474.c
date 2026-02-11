init_pluginsys(void){

	if (plugin_univ) {
		return TRUE;
	}

	plugin_univ = NewPILPluginUniv(HA_PLUGIN_DIR);

	if (plugin_univ) {
		if (PILLoadPlugin(plugin_univ, PI_IFMANAGER, "generic", reqs)
		!=	PIL_OK){
			cl_log(LOG_ERR, "generic plugin load failed\n");
			DelPILPluginUniv(plugin_univ);
			plugin_univ = NULL;
		}
	}else{
		cl_log(LOG_ERR, "pi univ creation failed\n");
	}
	return plugin_univ != NULL;

}
