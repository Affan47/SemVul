init_auparse(void)
{
	auparse_state_t *au = NULL;
	if (stdin_flag) {
		au = auparse_init(AUSOURCE_FILE_POINTER, stdin);
	} else if (file) {
		au = auparse_init(AUSOURCE_FILE, file);
	} else {
		if (getuid()) {
			fprintf(stderr, "You probably need to be root for "
					"this to work\n");
		}
		au = auparse_init(AUSOURCE_LOGS, NULL);
	}
	if (au == NULL) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
	}
	return au;
}
