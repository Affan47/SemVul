xmlnode_handle_end(void *data, const char *name)
{
	session_t *s = (session_t *) data;
	xmlnode_t *n;
	jabber_private_t *j;

	if (!s || !(j = s->priv) || !name) {
		debug_error("[jabber] xmlnode_handle_end() invalid parameters\n");
		return;
	}

	if (!(n = j->node)) {


		debug("[jabber] end tag within <stream>, ignoring\n");
		return;
	}

	if (!n->parent) {
		jabber_handle(data, n);
		xmlnode_free(n);
		j->node = NULL;
		return;
	} else {
		j->node = n->parent;
	}
}
