check_include(char *buf)
{
	char *str;
	vector_t *strvec;
	char *path;
	int ret;

	strvec = alloc_strvec(buf);

	if (!strvec){
		return 0;
	}
	str = vector_slot(strvec, 0);

	if (!strcmp(str, EOB)) {
		free_strvec(strvec);
		return 0;
	}

	if(!strcmp("include", str) && vector_size(strvec) == 2){
		char *conf_file = vector_slot(strvec, 1);

		FILE *prev_stream = current_stream;
		char *prev_conf_file = current_conf_file;
		char prev_path[MAXBUF];
		path = getcwd(prev_path, MAXBUF);
		if (!path) {
			log_message(LOG_INFO, "getcwd(%s) error (%s)\n"
					    , prev_path, strerror(errno));
		}

		read_conf_file(conf_file);
		current_stream = prev_stream;
		current_conf_file = prev_conf_file;
		ret = chdir(prev_path);
		if (ret < 0) {
			log_message(LOG_INFO, "chdir(%s) error (%s)\n"
					    , prev_path, strerror(errno));
		}
		return 1;
	}
	free_strvec(strvec);
	return 0;
}
