do_register(const void *data)
{
	struct dundi_ie_data ied;
	struct dundi_peer *peer = (struct dundi_peer *)data;
	char eid_str[20];
	char eid_str2[20];
	ast_debug(1, "Register us as '%s' to '%s'\n", ast_eid_to_str(eid_str, sizeof(eid_str), &peer->us_eid), ast_eid_to_str(eid_str2, sizeof(eid_str2), &peer->eid));
	peer->registerid = ast_sched_add(sched, default_expiration * 1000, do_register, data);

	if (peer->regtrans)
		destroy_trans(peer->regtrans, 0);
	peer->regtrans = create_transaction(peer);
	if (peer->regtrans) {
		ast_set_flag(peer->regtrans, FLAG_ISREG);
		memset(&ied, 0, sizeof(ied));
		dundi_ie_append_short(&ied, DUNDI_IE_VERSION, DUNDI_DEFAULT_VERSION);
		dundi_ie_append_eid(&ied, DUNDI_IE_EID, &peer->regtrans->us_eid);
		dundi_ie_append_short(&ied, DUNDI_IE_EXPIRATION, default_expiration);
		dundi_send(peer->regtrans, DUNDI_COMMAND_REGREQ, 0, 0, &ied);

	} else
		ast_log(LOG_NOTICE, "Unable to create new transaction for registering to '%s'!\n", ast_eid_to_str(eid_str, sizeof(eid_str), &peer->eid));

	return 0;
}
