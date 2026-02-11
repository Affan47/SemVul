process_logs(void)
{
	struct daemon_conf config;
	char *filename;
	int len, num = 0;

	if (user_file && userfile_is_dir) {
		char dirname[MAXPATHLEN];
		clear_config (&config);

		strcpy(dirname, user_file);
		if (dirname[strlen(dirname)-1] != '/')
			strcat(dirname, "/");
		strcat (dirname, "audit.log");
		free((void *)config.log_file);
		config.log_file=strdup(dirname);
		fprintf(stderr, "NOTE - using logs in %s\n", config.log_file);
	} else {

       		if (load_config(&config, TEST_SEARCH))
			fprintf(stderr, "NOTE - using built-in logs: %s\n",
				config.log_file);
	}


	len = strlen(config.log_file) + 16;
	filename = malloc(len);
	if (!filename) {
		fprintf(stderr, "No memory\n");
		free_config(&config);
		return 1;
	}

	snprintf(filename, len, "%s", config.log_file);
	do {
		if (access(filename, R_OK) != 0)
			break;

		num++;
		snprintf(filename, len, "%s.%d", config.log_file, num);
	} while (1);
	num--;


	files_to_process = num;


	if (num > 0)
		snprintf(filename, len, "%s.%d", config.log_file, num);
	else
		snprintf(filename, len, "%s", config.log_file);
	do {
		int ret;
		if ((ret = process_file(filename))) {
			free(filename);
			free_config(&config);
			return ret;
		}


		files_to_process--;
		num--;
		if (num > 0)
			snprintf(filename, len, "%s.%d", config.log_file, num);
		else if (num == 0)
			snprintf(filename, len, "%s", config.log_file);
		else
			break;
	} while (1);
	free(filename);
	free_config(&config);
	return 0;
}
