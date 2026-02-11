imsp_fetchaddress(fbuf, cp, tag, id, host)
    fbuf_t *fbuf;
    command_t *cp;
    char *tag, *host;
    auth_id *id;
{
    char *name = NULL, *alias = NULL, *user;
    int result;

    user = auth_username(auth_level(id) >= AUTH_USER ? id : NULL);
    if ((name = copy_astring(fbuf, 1)) == NULL
	|| (alias = copy_astring(fbuf, 1)) == NULL) {
	SEND_RESPONSE(fbuf, tag, rpl_badfetchaddr);
    } else if (!abook_canfetch(id, name)) {
	im_send(fbuf, NULL, rpl_abookauth, tag, user, txt_access, name);
    } else {
	lcase(name);
	do {
	    if ((result = show_address(fbuf, id, name, alias)) < 0) break;
	    free(alias);
	    alias = copy_astring(fbuf, 1);
	} while (alias);
	if (result == -1) {
	    im_send(fbuf, NULL, rpl_noentry, tag, alias);
	} else if (alias == NULL && fbuf->upos != fbuf->lend) {
	    SEND_RESPONSE(fbuf, tag, rpl_badastr);
	} else {
	    SEND_RESPONSE1(fbuf, tag, rpl_complete, cp->word);
	}
    }
    if (alias) free(alias);
    if (name) free(name);
}
