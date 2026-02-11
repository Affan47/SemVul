annotate_fetch_proxy(const char *server, const char *mbox_pat,
			 struct strlist *entry_pat,
			 struct strlist *attribute_pat)
{
    struct backend *be;
    struct strlist *l;
    char mytag[128];

    assert(server && mbox_pat && entry_pat && attribute_pat);

    be = proxy_findserver(server, &imap_protocol,
			  proxy_userid, &backend_cached,
			  &backend_current, &backend_inbox, imapd_in);
    if (!be) return IMAP_SERVER_UNAVAILABLE;


    proxy_gentag(mytag, sizeof(mytag));
    prot_printf(be->out, "%s GETANNOTATION \"%s\" (", mytag, mbox_pat);
    for (l = entry_pat; l; l = l->next) {
	prot_printf(be->out, "\"%s\"%s", l->s, l->next ? " " : "");
    }
    prot_printf(be->out, ") (");
    for (l = attribute_pat; l; l = l->next) {
	prot_printf(be->out, "\"%s\"%s", l->s, l->next ? " " : "");
    }
    prot_printf(be->out, ")\r\n");
    prot_flush(be->out);


    pipe_until_tag(be, mytag, 0);

    return 0;
}
