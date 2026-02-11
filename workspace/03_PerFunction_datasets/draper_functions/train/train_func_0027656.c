handle_prop_cmd(void) {
	char *value, *str, *done = "DONE";

	if (cmd_atom == None) {
		return;
	}

	value = get_xprop(cmd_atom_str, root);
	if (value == NULL) {
		return;
	}

	str = lblanks(value);
	if (!strcmp(str, done)) {
		free(value);
		return;
	}
	if (strstr(str, "cmd=quit") == str || strstr(str, "\ncmd=quit")) {
		set_xprop(cmd_atom_str, root, done);
		appshare_cleanup(0);
	}

	process_string(str);

	free(value);
	set_xprop(cmd_atom_str, root, done);
}
