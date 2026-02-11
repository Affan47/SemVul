n_set(struct Luser *lptr, int ac, char **av)
{
	struct Command *cptr = NULL;
	struct NickInfo *nptr = NULL;
	struct NickInfo *sender = NULL;

	if (ac < 3)
	{
		notice(n_NickServ, lptr->nick,
			   "Syntax: \002SET <nickname> <option> [parameter]\002");
		notice(n_NickServ, lptr->nick, ERR_MORE_INFO, n_NickServ,
			   "SET");
		return;
	}

	if ((nptr = FindNick(av[1])) == NULL)
	{
		notice(n_NickServ, lptr->nick, ERR_NOT_REGGED, av[1]);
		return;
	}

	if (nptr->flags & NS_FORBID)
	{
		notice(n_NickServ, lptr->nick,
			   "Cannot execute commands for forbidden nicknames");
		return;
	}

	sender = FindNick(lptr->nick);

#ifdef LINKED_NICKNAMES

	if (!IsLinked(nptr, sender)
#ifdef EMPOWERADMINS_MORE
			&& !IsValidAdmin(lptr)
#endif
	   )
	{
		notice(n_NickServ, lptr->nick,
			   "Nickname [\002%s\002] is not linked with [\002%s\002]",
			   nptr->nick, lptr->nick);
		return;
	}
#endif

	cptr = GetCommand(setcmds, av[2]);

	if (cptr && (cptr != (struct Command *) -1))
	{

		(*cptr->func)(lptr, nptr, ac, av);
	}
	else
	{

		notice(n_NickServ, lptr->nick,
			   "%s switch [\002%s\002]",
			   (cptr == (struct Command *) -1) ? "Ambiguous" : "Unknown",
			   av[2]);
		notice(n_NickServ, lptr->nick, ERR_MORE_INFO, n_NickServ, "SET");
		return;
	}
}
