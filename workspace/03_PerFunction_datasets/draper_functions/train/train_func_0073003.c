check_control(void) {
	static int last_size = -1;
	static time_t last_mtime = 0;
	struct stat sb;
	char *control_cmd;

	if (!control) {
		return 1;
	}

	if (!strcmp(control, "internal")) {
		return 1;
	}

	control_cmd = (char *)malloc(strlen(control) + strlen(".cmd") + 1);
	sprintf(control_cmd, "%s.cmd", control);
	if (stat(control_cmd, &sb) == 0) {
		FILE *f;
		if (sb.st_size > 0) {
			process_control(control_cmd, 0);
		}
		f = fopen(control_cmd, "w");
		if (f) {
			fclose(f);
		}
	}
	free(control_cmd);

	if (stat(control, &sb) != 0) {
		return 1;
	}
	if (last_size == (int) sb.st_size && last_mtime == sb.st_mtime) {
		return 1;
	}
	last_size = (int) sb.st_size;
	last_mtime = sb.st_mtime;

	return process_control(control, 1);
}
