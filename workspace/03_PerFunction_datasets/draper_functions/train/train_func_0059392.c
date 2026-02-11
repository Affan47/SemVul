encname(struct mailbox *mp, const char *name, int same, const char *box)
{
	char	*cachedir, *eaccount, *emailbox, *ename, *res;
	int	resz;

	ename = strenc(name);
	if (mp->mb_cache_directory && same && box == NULL) {
		res = salloc(resz = strlen(mp->mb_cache_directory) +
				strlen(ename) + 2);
		snprintf(res, resz, "%s%s%s", mp->mb_cache_directory,
				*ename ? "/" : "", ename);
	} else {
		if ((cachedir = value("imap-cache")) == NULL)
			return NULL;
		cachedir = expand(cachedir);
		eaccount = strenc(mp->mb_imap_account);
		if (box)
			emailbox = strenc(box);
		else if (asccasecmp(mp->mb_imap_mailbox, "INBOX"))
			emailbox = strenc(mp->mb_imap_mailbox);
		else
			emailbox = "INBOX";
		res = salloc(resz = strlen(cachedir) + strlen(eaccount) +
				strlen(emailbox) + strlen(ename) + 4);
		snprintf(res, resz, "%s/%s/%s%s%s",
				cachedir, eaccount, emailbox,
				*ename ? "/" : "", ename);
	}
	return res;
}
