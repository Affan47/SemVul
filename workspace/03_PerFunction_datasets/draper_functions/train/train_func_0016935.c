tcpcon_makeallocnegotiatemsg(int hostid, char cryptkey[NEGOTIATE_CRYPTKEY_SIZE], struct negotiate_msg **msgret) {
	struct negotiate_msg *msg;
	struct configfile_algo_pref *cryptalgopref, *compalgopref;
	int i;
	if(!NODEINFO_EXISTS(hostid)) return TCPCON_ERROR;

	cryptalgopref = getDefaultCryptAlgos();
	compalgopref = getDefaultCompAlgos();
	if(global_config.cryptalgos) cryptalgopref = global_config.cryptalgos;
	if(global_config.compalgos) compalgopref = global_config.compalgos;
	if(NODEINFO_INFO(hostid).options) if(NODEINFO_INFO(hostid).options->cryptalgos) cryptalgopref = NODEINFO_INFO(hostid).options->cryptalgos;
	if(NODEINFO_INFO(hostid).options) if(NODEINFO_INFO(hostid).options->compalgos) compalgopref = NODEINFO_INFO(hostid).options->compalgos;

	msg = malloc(sizeof(struct negotiate_msg));
	memset(msg, 0, sizeof(struct negotiate_msg));

	for(i = 0; cryptalgopref[i].algo >= 0 && i < NEGOTIATE_ALGOLIST_SIZE; i++) {
		msg->cryptalgos[i].algoid = htonl(cryptalgopref[i].algo);
		msg->cryptalgos[i].level = htons(cryptalgopref[i].level);
		msg->cryptalgos[i].preference = htonl(cryptalgopref[i].pref);
	}
	if(i < NEGOTIATE_ALGOLIST_SIZE) msg->cryptalgos[i].algoid = htonl(-1);
	for(i = 0; compalgopref[i].algo >= 0 && i < NEGOTIATE_ALGOLIST_SIZE; i++) {
		msg->compalgos[i].algoid = htonl(compalgopref[i].algo);
		msg->compalgos[i].level = htons(compalgopref[i].level);
		msg->compalgos[i].preference = htonl(compalgopref[i].pref);
	}
	if(i < NEGOTIATE_ALGOLIST_SIZE) msg->compalgos[i].algoid = htonl(-1);

	memcpy(msg->cryptkey, cryptkey, NEGOTIATE_CRYPTKEY_SIZE);
	*msgret = msg;
	return TCPCON_OK;
}
