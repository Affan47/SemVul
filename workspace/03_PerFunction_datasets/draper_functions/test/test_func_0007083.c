handle_stanza(LmMessageHandler *handler, LmConnection *connection,
    LmMessage *lmsg, gpointer user_data)
{
	XMPP_SERVER_REC *server;
	int type;
	const char *id;
	char *from, *to, *raw;

	if ((server = XMPP_SERVER(user_data)) == NULL)
		return LM_HANDLER_RESULT_REMOVE_MESSAGE;
	raw = xmpp_recode_in(lm_message_node_to_string(lmsg->node));
	signal_emit("xmpp xml in", 2, server, raw);
	g_free(raw);
	type = lm_message_get_sub_type(lmsg);
	id = lm_message_node_get_attribute(lmsg->node, "id");
	if (id == NULL)
		id = "";
	from = xmpp_recode_in(lm_message_node_get_attribute(lmsg->node, "from"));
	if (from == NULL)
		from = g_strdup("");
	to = xmpp_recode_in(lm_message_node_get_attribute(lmsg->node, "to"));
	if (to == NULL)
		to = g_strdup("");
	switch(lm_message_get_type(lmsg)) {
	case LM_MESSAGE_TYPE_MESSAGE:
		signal_emit("xmpp recv message", 6,
		    server, lmsg, type, id, from, to);
		break;
	case LM_MESSAGE_TYPE_PRESENCE:
		signal_emit("xmpp recv presence", 6,
		    server, lmsg, type, id, from, to);
		break;
	case LM_MESSAGE_TYPE_IQ:
		signal_emit("xmpp recv iq", 6,
		    server, lmsg, type, id, from, to);
		break;
	default:
		signal_emit("xmpp recv others", 6,
		    server, lmsg, type, id, from, to);
		break;
	}
	g_free(from);
	g_free(to);
	return LM_HANDLER_RESULT_REMOVE_MESSAGE;
}
