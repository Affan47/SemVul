purgecache(struct mailbox *mp, struct message *m, long mc)
{
	char	*name;
	struct cw	cw;

	if ((name = encname(mp, "", 1, NULL)) == NULL)
		return;
	if (cwget(&cw) == STOP)
		return;
	purge(mp, m, mc, &cw, name);
	cwrelse(&cw);
}
