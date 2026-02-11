own_join(MUC_REC *channel, const char *nickname,
    const char *full_jid, const char *affiliation, const char *role,
    gboolean forced)
{
	XMPP_NICK_REC *nick;

	if (channel->joined)
		return;
	if ((nick = xmpp_nicklist_find(channel, nickname)) != NULL)
		return;
	nick = xmpp_nicklist_insert(channel, nickname, full_jid);
	nicklist_set_own(CHANNEL(channel), NICK(nick));
	channel->chanop = channel->ownnick->op;
	xmpp_nicklist_set_modes(nick,
	    xmpp_nicklist_get_affiliation(affiliation),
	    xmpp_nicklist_get_role(role));
	channel->names_got = TRUE;
	channel->joined = TRUE;
	signal_emit("message join", 4, channel->server, channel->name,
	    nick->nick, nick->host);
	signal_emit("message xmpp muc mode", 4, channel,
	    nick->nick, nick->affiliation, nick->role);
	signal_emit("channel joined", 1, channel);
	signal_emit("channel sync", 1, channel);
	channel_send_autocommands(CHANNEL(channel));
	if (forced)
		nick_changed(channel, channel->nick, nick->nick);
	if (*channel->mode == '\0')
		disco_request(channel->server, channel->name);
}
