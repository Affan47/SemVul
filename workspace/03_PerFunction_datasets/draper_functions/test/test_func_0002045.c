c_setpass(struct Luser *lptr, struct NickInfo *nptr, int ac, char **av)

{
	struct ChanInfo *cptr;
	struct f_users *fdrs;

	if (ac < 3)
	{
		notice(n_ChanServ, lptr->nick,
		       "Syntax: \002SETPASS <channel> <password>\002");
		notice(n_ChanServ, lptr->nick,
		       ERR_MORE_INFO,
		       n_ChanServ,
		       "SETPASS");
		return;
	}

	RecordCommand("%s: %s!%s@%s SETPASS [%s] ...",
	              n_ChanServ,
	              lptr->nick,
	              lptr->username,
	              lptr->hostname,
	              av[1]);

	o_Wallops("SETPASS from %s!%s@%s for channel [%s]",
	          lptr->nick,
	          lptr->username,
	          lptr->hostname,
	          av[1] );

	if (!(cptr = FindChan(av[1])))
	{
		notice(n_ChanServ, lptr->nick,
		       ERR_CH_NOT_REGGED,
		       av[1]);
		return;
	}

	if (!ChangeChanPass(cptr, av[2]))
	{
		notice(n_ChanServ, lptr->nick,
		       "Password change failed");
		RecordCommand("%s: Failed to change password for [%s] to [%s] (SETPASS)",
		              n_ChanServ,
		              cptr->name,
		              av[2]);
		return;
	}


	while (cptr->founders)
	{
		fdrs = cptr->founders->next;
		RemFounder(cptr->founders->lptr, cptr);
		cptr->founders = fdrs;
	}

	notice(n_ChanServ, lptr->nick,
	       "Founder password for %s has been changed to [\002%s\002]",
	       cptr->name,
	       av[2]);
}
