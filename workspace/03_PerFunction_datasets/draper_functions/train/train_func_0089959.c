xmlrpc_command_success_nodata(sourceinfo_t *si, const char *message)
{
	connection_t *cptr;
	struct httpddata *hd;
	char *newmessage;
	char *p;

	newmessage = xmlrpc_normalizeBuffer(message);

	cptr = si->connection;
	hd = cptr->userdata;
	if (hd->sent_reply)
		return;
	if (hd->replybuf != NULL)
	{
		hd->replybuf = srealloc(hd->replybuf, strlen(hd->replybuf) + strlen(newmessage) + 2);
		p = hd->replybuf + strlen(hd->replybuf);
		*p++ = '\n';
	}
	else
	{
		hd->replybuf = smalloc(strlen(newmessage) + 1);
		p = hd->replybuf;
	}
        strcpy(p, newmessage);
	free(newmessage);
}
