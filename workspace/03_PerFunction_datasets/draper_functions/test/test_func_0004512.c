init(void* args) {
	String fname(cv["ipgroups"]);
	if (fname.length() > 0) {
		return readIPMelangeList(fname.toCharArray());
	} else {
		if (!is_daemonised)
			std::cerr << "No ipgroups file defined in IP auth plugin config" << std::endl;
		syslog(LOG_ERR, "No ipgroups file defined in IP auth plugin config");
		return -1;
	}
}
