process_logs(struct daemon_conf *config)
{
	char *filename;
	int len, num = 0;


	len = strlen(config->log_file) + 16;
	filename = malloc(len);
	if (!filename) {
		fprintf(stderr, "No memory\n");
		return 1;
	}

	snprintf(filename, len, "%s", config->log_file);
	do {
		if (access(filename, R_OK) != 0)
			break;

		num++;
		snprintf(filename, len, "%s.%d", config->log_file, num);
	} while (1);
	num--;


	if (num > 0)
		snprintf(filename, len, "%s.%d", config->log_file, num);
	else
		snprintf(filename, len, "%s", config->log_file);
	do {
		int ret;
		if ((ret = process_file(filename))) {
			free(filename);
			return ret;
		}


		num--;
		if (num > 0)
			snprintf(filename, len, "%s.%d", config->log_file, num);
		else if (num == 0)
			snprintf(filename, len, "%s", config->log_file);
		else
			break;
	} while (1);
	free(filename);
	return 0;
}
