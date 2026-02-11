magictrash()
{
	const char *p;

	p=getenv("IMAP_MOVE_EXPUNGE_TO_TRASH");

	if (p && atoi(p))
		return 1;
	return 0;
}
