vcard_handle(XMPP_SERVER_REC *server, const char *jid, LmMessageNode *node)
{
	LmMessageNode *child, *subchild;
	GHashTable *ht;
	const char *adressing;
	char *value;

	ht = g_hash_table_new_full(g_str_hash, g_str_equal,
	    NULL, g_free);
	child = node->children;
	while (child != NULL) {

		if (g_ascii_strcasecmp(child->name, "PHOTO") == 0)
			goto next;
		if (child->value != NULL) {
			value = xmpp_recode_in(child->value);
			g_strstrip(value);
			g_hash_table_insert(ht, child->name, value);
			goto next;
		}

		subchild = child->children;
		adressing = NULL;
		while (subchild != NULL && adressing == NULL) {
			if (subchild->value == NULL && (
			    g_ascii_strcasecmp(subchild->name , "HOME") == 0 ||
			    g_ascii_strcasecmp(subchild->name , "WORK") == 0))
				adressing = subchild->name;
			subchild = subchild->next;
		}
		subchild = child->children;
		while (subchild != NULL) {
			if (subchild->value != NULL) {
				value = xmpp_recode_in(subchild->value);

				g_free(value);
			}
			subchild = subchild->next;
		}

next:
		child = child->next;
	}
	signal_emit("xmpp vcard", 3, server, jid, ht);
	g_hash_table_destroy(ht);
}
