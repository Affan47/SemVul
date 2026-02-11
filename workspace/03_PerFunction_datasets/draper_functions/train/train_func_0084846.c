option_color_command(int argc, const char *argv[])
{
	struct line_info *info;

	if (argc != 3 && argc != 4) {
		config_msg = "Wrong number of arguments given to color command";
		return ERR;
	}

	info = get_line_info(argv[0]);
	if (!info) {
		if (!string_enum_compare(argv[0], "main-delim", strlen("main-delim"))) {
			info = get_line_info("delimiter");

		} else if (!string_enum_compare(argv[0], "main-date", strlen("main-date"))) {
			info = get_line_info("date");

		} else {
			config_msg = "Unknown color name";
			return ERR;
		}
	}

	if (set_color(&info->fg, argv[1]) == ERR ||
	    set_color(&info->bg, argv[2]) == ERR) {
		config_msg = "Unknown color";
		return ERR;
	}

	if (argc == 4 && set_attribute(&info->attr, argv[3]) == ERR) {
		config_msg = "Unknown attribute";
		return ERR;
	}

	return OK;
}
