_run_script(struct cmd_context *cmd, int argc, char **argv)
{
	FILE *script;

	char buffer[CMD_LEN];
	int ret = 0;
	int magic_number = 0;
	char *script_file = argv[0];

	if ((script = fopen(script_file, "r")) == NULL)
		return ENO_SUCH_CMD;

	while (fgets(buffer, sizeof(buffer), script) != NULL) {
		if (!magic_number) {
			if (buffer[0] == '#' && buffer[1] == '!')
				magic_number = 1;
			else {
				ret = ENO_SUCH_CMD;
				break;
			}
		}
		if ((strlen(buffer) == sizeof(buffer) - 1)
		    && (buffer[sizeof(buffer) - 1] - 2 != '\n')) {
			buffer[50] = '\0';
			log_error("Line too long (max 255) beginning: %s",
				  buffer);
			ret = EINVALID_CMD_LINE;
			break;
		}
		if (lvm_split(buffer, &argc, argv, MAX_ARGS) == MAX_ARGS) {
			buffer[50] = '\0';
			log_error("Too many arguments: %s", buffer);
			ret = EINVALID_CMD_LINE;
			break;
		}
		if (!argc)
			continue;
		if (!strcmp(argv[0], "quit") || !strcmp(argv[0], "exit"))
			break;
		ret = lvm_run_command(cmd, argc, argv);
		if (ret != ECMD_PROCESSED) {
			if (!error_message_produced()) {
				log_debug(INTERNAL_ERROR "Failed command did not use log_error");
				log_error("Command failed with status code %d.", ret);
			}
			break;
		}
	}

	if (fclose(script))
		log_sys_error("fclose", script_file);

	return ret;
}
