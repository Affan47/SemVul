c_forget(struct Luser *lptr, struct NickInfo *nptr, int ac, char **av)

{
	struct ChanInfo *cptr;

	if (ac < 2)
	{
		notice(n_ChanServ, lptr->nick,
		       "Syntax: \002FORGET <channel>\002");
		notice(n_ChanServ, lptr->nick,
		       ERR_MORE_INFO,
		       n_ChanServ,
		       "FORGET");
		return;
	}

	RecordCommand("%s: %s!%s@%s FORGET [%s]",
	              n_ChanServ, lptr->nick, lptr->username, lptr->hostname,
	              av[1]);

	o_Wallops("Forget from %s!%s@%s for channel [%s]",
	          lptr->nick, lptr->username, lptr->hostname,
	          av[1] );


	if ((cptr = FindChan(av[1])))
	{

		if (cptr->flags & CS_FORGET)
		{
			notice(n_ChanServ, lptr->nick,
			       "The channel [\002%s\002] is already forgotten",
			       cptr->name);
			return;
		}


		DeleteChan(cptr);
	}
	else
	{
		if (av[1][0] != '#')
		{
			notice(n_ChanServ, lptr->nick,
			       "[\002%s\002] is an invalid channel",
			       av[1]);
			return;
		}
	}

	cptr = MakeChan();
	cptr->name = MyStrdup(av[1]);
	cptr->created = current_ts;
	cptr->flags = CS_FORGET;
	SetDefaultALVL(cptr);

	AddChan(cptr);

	notice(n_ChanServ, lptr->nick,
	       "The channel [\002%s\002] is now forgotten",
	       av[1]);
}
