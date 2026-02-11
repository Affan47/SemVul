xref_cb(const char *msgid __attribute__((unused)),
		   const char *mailbox,
		   time_t mark __attribute__((unused)),
		   unsigned long uid, void *rock)
{
    struct xref_rock *xrock = (struct xref_rock *) rock;
    size_t len = strlen(xrock->buf);


    if (is_newsgroup(mailbox)) {
	snprintf(xrock->buf + len, xrock->size - len,
		 " %s:%lu", mailbox + strlen(newsprefix), uid);
    }

    return 0;
}
