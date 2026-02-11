message_write_searchaddr(ibuf, addrlist)
struct ibuf *ibuf;
struct address *addrlist;
{
    int prevaddr = 0;
    char* tmp;

    while (addrlist) {


	if (!addrlist->domain) {
	    if (addrlist->mailbox) {
		if (prevaddr) PUTIBUF(ibuf, ',');

		tmp = charset_decode_mimeheader(addrlist->mailbox, NULL, 0);
		message_write_text(ibuf, tmp);
		free(tmp);
		tmp = NULL;
		PUTIBUF(ibuf, ':');


		prevaddr = 0;
	    }
	    else {
		PUTIBUF(ibuf, ';');
		prevaddr = 1;
	    }
	}
	else {
	    if (prevaddr) PUTIBUF(ibuf, ',');

	    if (addrlist->name) {
		tmp = charset_decode_mimeheader(addrlist->name, NULL, 0);
		message_write_text(ibuf, tmp);
		free(tmp); tmp = NULL;
		PUTIBUF(ibuf, ' ');
	    }

	    PUTIBUF(ibuf, '<');
	    if (addrlist->route) {
		message_write_text_lcase(ibuf, addrlist->route);
		PUTIBUF(ibuf, ':');
	    }

	    message_write_text_lcase(ibuf, addrlist->mailbox);
	    PUTIBUF(ibuf, '@');

	    message_write_text_lcase(ibuf, addrlist->domain);
	    PUTIBUF(ibuf, '>');
	    prevaddr = 1;
	}

	addrlist = addrlist->next;
    }
}
