event_privmsg(IRC_SERVER_REC *server, const char *data,
			  const char *nick, const char *addr)
{
	char *params, *target, *msg, *recoded;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 2 | PARAM_FLAG_GETREST, &target, &msg);
	if (nick == NULL) nick = server->real_address;
	if (addr == NULL) addr = "";
	if (*target == '@' && ischannel(target[1])) {

		recoded = recode_in(SERVER(server), msg, target+1);
		signal_emit("message irc op_public", 5,
			    server, recoded, nick, addr,
			    get_visible_target(server, target+1));
	} else {
		recoded = recode_in(SERVER(server), msg, ischannel(*target) ? target : nick);
		signal_emit(ischannel(*target) ?
			    "message public" : "message private", 5,
			    server, recoded, nick, addr,
			    get_visible_target(server, target));
	}

	g_free(params);
	g_free(recoded);
}
