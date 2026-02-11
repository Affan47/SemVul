is_outbox(const char *mailbox)
{
	const char *p=getenv("OUTBOX");

	if (strncmp(mailbox, "./", 2) == 0)
		mailbox += 2;

	if (p == NULL || *p == 0 || strcmp(p, mailbox))
		return (0);

	return (1);
}
