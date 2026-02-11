loadDMPlugins()
{
	std::deque<String > dq = findoptionM("downloadmanager");
	unsigned int numplugins = dq.size();
	if (numplugins < 1) {
		if (!is_daemonised) {
			std::cerr << "There must be at least one download manager option" << std::endl;
		}
		syslog(LOG_ERR, "%s", "There must be at least one download manager option");
		return false;
	}
	String config;
	for (unsigned int i = 0; i < numplugins; i++) {
		config = dq[i];
#ifdef DGDEBUG
		std::cout << "loading download manager config: " << config << std::endl;
#endif
		DMPlugin *dmpp = dm_plugin_load(config.toCharArray());
		if (dmpp == NULL) {
			if (!is_daemonised) {
				std::cerr << "dm_plugin_load() returned NULL pointer with config file: " << config << std::endl;
			}
			syslog(LOG_ERR, "dm_plugin_load() returned NULL pointer with config file: %s", config.toCharArray());
			return false;
		}
		bool lastplugin = (i == (numplugins - 1));
		int rc = dmpp->init(&lastplugin);
		if (rc < 0) {
			if (!is_daemonised) {
				std::cerr << "Download manager plugin init returned error value: " << rc << std::endl;
			}
			syslog(LOG_ERR, "Download manager plugin init returned error value: %d", rc);
			return false;
		}
		else if (rc > 0) {
			if (!is_daemonised) {
				std::cerr << "Download manager plugin init returned warning value: " << rc << std::endl;
			}
			syslog(LOG_ERR, "Download manager plugin init returned warning value: %d", rc);
		}
		dmplugins.push_back(dmpp);
	}

	dmplugins_begin = dmplugins.begin();
	dmplugins_end = dmplugins.end();
	return true;
}
