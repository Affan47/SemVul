checkcommand(struct io_data *io_data, __maybe_unused SOCKETTYPE c, char *param, bool isjson, char group)
{
	struct api_data *root = NULL;
	bool io_open;
	char cmdbuf[100];
	bool found, access;
	int i;

	if (param == NULL || *param == '\0') {
		message(io_data, MSG_MISCHK, 0, NULL, isjson);
		return;
	}

	found = false;
	access = false;
	for (i = 0; cmds[i].name != NULL; i++) {
		if (strcmp(cmds[i].name, param) == 0) {
			found = true;

			sprintf(cmdbuf, "|%s|", param);
			if (ISPRIVGROUP(group) || strstr(COMMANDS(group), cmdbuf))
				access = true;

			break;
		}
	}

	message(io_data, MSG_CHECK, 0, NULL, isjson);
	io_open = io_add(io_data, isjson ? COMSTR JSON_CHECK : _CHECK COMSTR);

	root = api_add_const(root, "Exists", found ? YES : NO, false);
	root = api_add_const(root, "Access", access ? YES : NO, false);

	root = print_data(io_data, root, isjson, false);
	if (isjson && io_open)
		io_close(io_data);
}
