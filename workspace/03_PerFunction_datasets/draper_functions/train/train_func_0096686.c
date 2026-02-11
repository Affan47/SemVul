show_address(fbuf, id, name, alias)
    fbuf_t *fbuf;
    auth_id *id;
    char *name, *alias;
{
    abook_state astate;
    abook_fielddata *fetch;
    int count, i, freedata;

    if ((fetch = abook_fetch(&astate, id, name, alias, &count, &freedata))) {
	im_send(fbuf, NULL, msg_fetchaddr, name, alias);
	for (i = 0; i < count; ++i) {
	    im_send(fbuf, NULL, msg_fielddata,
				fetch[i].field, fetch[i].data);
	}
	SEND_STRING(fbuf, "\r\n");
	abook_fetchdone(&astate, fetch, count, freedata);
    }

    return (fetch ? 0 : -1);
}
