alloc_search_notkey(struct searchinfo **head)
{
struct imaptoken *t=currenttoken();

	if (t->tokentype == IT_ATOM && strcmp(t->tokenbuf, "NOT") == 0)
	{
	struct searchinfo *si=alloc_search(head);

		si->type=search_not;
		nexttoken();
		if ((si->a=alloc_search_key(head)) == 0)
			return (0);
		return (si);
	}
	return (alloc_search_key(head));
}
