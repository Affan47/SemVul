setup_log_file_array(auparse_state_t *au)
{
        struct daemon_conf config;
        char *filename, **tmp;
        int len, num = 0, i = 0;


	set_aumessage_mode(MSG_STDERR, DBG_NO);
	load_config(&config, TEST_SEARCH);


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

	if (num == 0) {
		fprintf(stderr, "No log file\n");
		free_config(&config);
		free(filename);
		return 1;
	}
	num--;
	tmp = malloc((num+2)*sizeof(char *));


	if (num > 0)
		snprintf(filename, len, "%s.%d", config.log_file, num);
	else
		snprintf(filename, len, "%s", config.log_file);
	do {
		tmp[i++] = strdup(filename);


		num--;
		if (num > 0)
			snprintf(filename, len, "%s.%d", config.log_file, num);
		else if (num == 0)
			snprintf(filename, len, "%s", config.log_file);
		else
			break;
	} while (1);
	free_config(&config);
	free(filename);


	tmp[i] = NULL;
	au->source_list = tmp;
	return 0;
}
