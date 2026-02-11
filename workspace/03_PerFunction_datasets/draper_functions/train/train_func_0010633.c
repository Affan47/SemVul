newnews_cb(const char *msgid, const char *rcpt, time_t mark,
		      unsigned long uid, void *rock)
{
    static char lastid[1024];
    struct newrock *nrock = (struct newrock *) rock;


    if (!msgid) {
	lastid[0] = '\0';
	return 0;
    }


    if (strcmp(msgid, lastid) && mark >= nrock->tstamp &&
	uid && is_newsgroup(rcpt)) {
	struct wildmat *wild = nrock->wild;


	while (wild->pat && wildmat(rcpt, wild->pat) != 1) wild++;


	if (wild->pat && !wild->not) {
	    prot_printf(nntp_out, "%s\r\n", msgid);
	    strlcpy(lastid, msgid, sizeof(lastid));
	}
    }

    return 0;
}
