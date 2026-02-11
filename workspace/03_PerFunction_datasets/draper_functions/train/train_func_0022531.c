set_auth_pubtkt_debug(cmd_parms *cmd, void *cfg, const char *param) {
	auth_pubtkt_dir_conf *conf = (auth_pubtkt_dir_conf*)cfg;

	int debug = atoi(param);

	if (debug < 0)        return ("Debug level must be positive");
	if (debug == INT_MAX) return ("Integer overflow or invalid number");

	conf->debug = debug;

	return NULL;
}
