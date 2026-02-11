conf_init(const char *path)
{
	char host_name[256];
	static conf cfg[] = {
		{ "delay", TYPE_INTEGER, { 0 } },
		{ "encryption_method", TYPE_STRING, { NULL } },
		{ "identity", TYPE_STRING, { NULL } },
		{ "password", TYPE_STRING, { NULL } },
		{ "port", TYPE_STRING, { NULL } },
		{ "server", TYPE_STRING, { NULL } },
		{ "timeout", TYPE_INTEGER, { 0 } },
		{ "tls_ciphers", TYPE_STRING, { NULL } },
		{ NULL, TYPE_NONE, { NULL } }
	};

	debug("Initializing configuration context");

	if (gethostname(host_name, sizeof(host_name)) == -1)
		die("Cannot get host name: %m");

	conf_setstr(cfg, "identity", host_name);
	conf_setstr(cfg, "password", DEFAULT_PASSWORD);
	conf_setstr(cfg, "port", DEFAULT_PORT);
	conf_setstr(cfg, "server", DEFAULT_SERVER);
	conf_setint(cfg, "timeout", DEFAULT_TIMEOUT);
	conf_setstr(cfg, "tls_ciphers", DEFAULT_TLS_CIPHERS);

	parse_conf_file(path, cfg);

	return cfg;
}
