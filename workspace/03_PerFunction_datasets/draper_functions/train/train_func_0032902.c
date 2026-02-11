bofh_chkbadmx(const char *p)
{
	struct bofh_list *b;

	if (strncasecmp(p, "::ffff:", 7) == 0)
		p += 7;

	for (b=bofh_badmx; b; b=b->next)
	{
		if (strcmp(b->name, p) == 0)
			return (1);
	}
	return (0);
}
