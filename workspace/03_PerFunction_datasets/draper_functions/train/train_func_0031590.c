GetLink(char *nickname)

{
	struct NickInfo *nptr;

	if (!(nptr = FindNick(nickname)))
		return (NULL);

#ifdef LINKED_NICKNAMES

	if (nptr->master)
		return (nptr->master);
#endif

	return (nptr);
}
