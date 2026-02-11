cmd_passenger_pre_start(cmd_parms *cmd, void *pcfg, const char *arg) {
	serverConfig.prestartURLs.insert(arg);
	return NULL;
}
