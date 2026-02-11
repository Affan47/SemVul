jabber_dcc_find(const char *uin,  const char *id, const char *sid) {
#define DCC_RULE(x) (!xstrncmp(x->uid, "xmpp:", 5) && !xstrcmp(x->uid+5, uin))
	dcc_t *d;
	if (!id && !sid) { debug_error("jabber_dcc_find() neither id nor sid passed.. Returning NULL\n"); return NULL; }

	for (d = dccs; d; d = d->next) {
		jabber_dcc_t *p = d->priv;

		if (DCC_RULE(d) && (!sid || !xstrcmp(p->sid, sid)) && (!id || !xstrcmp(p->req, id))) {
			debug_function("jabber_dcc_find() %s sid: %s id: %s founded: 0x%x\n", __(uin), __(sid), __(id), d);
			return d;
		}
	}
	debug_error("jabber_dcc_find() %s %s not founded. Possible abuse attempt?!\n", __(uin), __(sid));
	return NULL;
}
