_check_config_file() {
	std::map<std::string, std::string> configs;
    std::string log_config_file = g_dir + "/" + g_config_file;
	get_config_map(log_config_file.c_str(), configs);
	if (configs.empty()) {
        return 0;
    }

    std::string log_level_str = configs["log_level"];
    set_log_level(log_level_str.c_str());

    std::string rd = configs["retain_day"];
    if (!rd.empty()) {
        g_file_appender.set_retain_day(atoi(rd.c_str()));
    }

    std::string dir = configs["log_dir"];
    std::string log_file = configs["log_file"];
    int ret = 0;
    if (!log_file.empty()) {
        use_file_appender = true;
        if (!g_file_appender.is_inited()) {
            ret = g_file_appender.init(dir, log_file);
        }
    }
    return ret;
}
