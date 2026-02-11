c_delme(struct Luser *lptr, struct NickInfo *nptr, int ac, char **av)
{

	struct ChanInfo *cptr;
	struct NickInfo *mptr;
	struct AccessChannel *acptr = NULL;

	if (ac < 2)
	{
		notice(n_ChanServ, lptr->nick,
			   "Syntax: \002DELME <channel>\002");
		notice(n_ChanServ, lptr->nick,
			   ERR_MORE_INFO,
			   n_ChanServ,
			   "DELME");
		return;
	}

	if (!(cptr = FindChan(av[1])))
	{
		notice(n_ChanServ, lptr->nick, ERR_CH_NOT_REGGED, av[1]);
		return;
	}

	mptr = GetLink(nptr->nick);

	if (mptr && mptr->AccessChannels)
		for (acptr = mptr->AccessChannels; acptr; acptr = acptr->next)
			if (acptr->cptr == cptr)
				break;

	if (acptr == NULL)
	{
		notice(n_ChanServ, lptr->nick,
		       "You are not in the access list of [\002%s\002]",
		       cptr->name);

		return;
	}

	if (acptr->accessptr->level <= cptr->access_lvl[CA_AUTODEOP])
	{
		notice(n_ChanServ, lptr->nick,
		       "You cannot do that because you have AUTODEOP access level on [\002%s\002]",
		       cptr->name);

		return;
	}

	notice(n_ChanServ, lptr->nick,
	       "You have been removed from the access list of [\002%s\002]",
	       cptr->name);

	RecordCommand("%s: %s!%s@%s DELME [%s]",
				  n_ChanServ,
				  lptr->nick,
				  lptr->username,
				  lptr->hostname,
				  cptr->name);

	DeleteAccess(cptr, acptr->accessptr);
	DeleteAccessChannel(mptr, acptr);
}
