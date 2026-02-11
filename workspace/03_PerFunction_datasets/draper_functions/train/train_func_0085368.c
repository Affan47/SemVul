sig_recv_x(XMPP_SERVER_REC *server, LmMessage *lmsg, const int type,
    const char *id, const char *from, const char *to)
{
	LmMessageNode *node, *child;
	const char *url, *desc;
	char *url_recoded, *desc_recoded, *str;

	node = lm_find_node(lmsg->node, "x", XMLNS, XMLNS_OOB_X);
	if (node != NULL) {
		child = lm_message_node_get_child(node, "url");
		if (child == NULL || child->value == NULL)
			return;
		url = child->value;
		child = lm_message_node_get_child(node, "desc");
		desc = child != NULL ? child->value : NULL;
		url_recoded = xmpp_recode_in(url);
		if (desc != NULL) {
			desc_recoded = xmpp_recode_in(desc);
			str = g_strconcat(desc_recoded, ": ", url_recoded, (void *)NULL);
			g_free(url_recoded);
			g_free(desc_recoded);
		} else
			str = url_recoded;
		signal_emit("message private", 4, server, str, from, from);
		g_free(str);
	}
}
