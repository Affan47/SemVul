init()
{
	char buf[512];
	std::string homedir=Glib::get_user_config_dir();
	snprintf(buf, 512, "%s/gmlive/pplive.lst", homedir.c_str());

	return read_channels(buf);
}
