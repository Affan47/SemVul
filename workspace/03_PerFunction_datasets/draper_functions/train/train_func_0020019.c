dessert_set_cli_port(uint16_t port) {
    if (_dessert_cli_running == 1) {
		dessert_err("CLI is already running!");
    	return DESSERT_ERR;
    }

	if (port >= 1024 && port <= 49151)
		_cli_port = port;
	else {
		port = 0;
		dessert_err("Port number has to be in [1024, 49151]");
	}
	dessert_info("CLI on port %d", _cli_port);
	return (port == 0 ? DESSERT_ERR : DESSERT_OK);
}
