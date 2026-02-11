display_values(char **controllers, int max, const char *group_name,
	char **names, int mode, const char *program_name)
{
	int ret, result = 0;


	if (mode & MODE_SHOW_HEADERS)
		printf("%s:\n", group_name);


	if (names[0] != NULL) {
		ret = display_name_values(names, group_name, program_name,
			mode);
		if (ret)
			result = ret;
	}


	if (controllers[0] != NULL) {
		ret = display_controller_values(controllers, group_name,
			program_name, mode);
		if (ret)
			result = ret;
	}


	if (mode & MODE_SHOW_HEADERS)
		printf("\n");

	return result;
}
