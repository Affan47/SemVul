c_status(struct Luser *lptr, struct NickInfo *nptr, int ac, char **av)

{
	struct ChanInfo *cptr;
	struct Luser *tmpuser;

	if (ac < 3)
	{
		notice(n_ChanServ, lptr->nick,
		       "Syntax: \002STATUS <channel> <nickname>\002");
		notice(n_ChanServ, lptr->nick,
		       ERR_MORE_INFO,
		       n_ChanServ,
		       "STATUS");
		return;
	}

	if (!(cptr = FindChan(av[1])))
	{
		notice(n_ChanServ, lptr->nick,
		       ERR_CH_NOT_REGGED,
		       av[1]);
		return;
	}

	if (!(tmpuser = FindClient(av[2])))
	{
		notice(n_ChanServ, lptr->nick,
		       "[\002%s\002] is not currently online",
		       av[2]);
		return;
	}

	notice(n_ChanServ, lptr->nick,
	       "%s has an access level of [\002%d\002] on %s",
	       tmpuser->nick, GetAccess(cptr, tmpuser), cptr->name);

	RecordCommand("%s: %s!%s@%s STATUS [%s] %s",
	              n_ChanServ, lptr->nick, lptr->username, lptr->hostname,
	              cptr->name, tmpuser->nick);
}
