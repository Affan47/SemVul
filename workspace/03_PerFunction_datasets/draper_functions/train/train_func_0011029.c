send_composing_event(XMPP_SERVER_REC *server, const char *dest, const char *id,
    gboolean composing)
{
	LmMessage *lmsg;
	LmMessageNode *node;
	char *recoded;

	recoded = xmpp_recode_out(dest);
	lmsg = lm_message_new_with_sub_type(recoded,
	    LM_MESSAGE_TYPE_MESSAGE, LM_MESSAGE_SUB_TYPE_CHAT);
	g_free(recoded);
	node = lm_message_node_add_child(lmsg->node, "x", NULL);
	lm_message_node_set_attribute(node, XMLNS, XMLNS_EVENT);
	if (composing)
		lm_message_node_add_child(node, "composing", NULL);
	if (id != NULL)
		lm_message_node_add_child(node, "id", id);
	signal_emit("xmpp send message", 2, server, lmsg);
	lm_message_unref(lmsg);
}
