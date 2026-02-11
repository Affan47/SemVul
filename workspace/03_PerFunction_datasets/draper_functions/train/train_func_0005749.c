AddHostToNick(char *host, struct NickInfo *nickptr)

{
	struct NickHost *hptr;

	if (!nickptr || !host)
		return;

	hptr = (struct NickHost *) MyMalloc(sizeof(struct NickHost));
	hptr->hostmask = MyStrdup(host);
	hptr->next = nickptr->hosts;
	nickptr->hosts = hptr;
}
