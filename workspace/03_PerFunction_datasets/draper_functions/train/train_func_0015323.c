cmd_gdb(char **arg)
{
	char *port_text = get_arg(arg);
	address_t port = 2000;

	if (port_text && expr_eval(stab_default, port_text, &port) < 0) {
		printc_err("gdb: can't parse port: %s\n", port_text);
		return -1;
	}

	if (port <= 0 || port > 65535) {
		printc_err("gdb: invalid port: %d\n", port);
		return -1;
	}

	do {
		if (gdb_server(port) < 0)
			return -1;
	} while (opdb_get_boolean("gdb_loop"));

	return 0;
}
