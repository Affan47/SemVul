c_set_founder(struct Luser *lptr, struct NickInfo *nptr, int ac, char **av)

{
	struct ChanInfo *cptr;
	struct NickInfo *fptr;

	if (!(cptr = FindChan(av[1])))
		return;

	if (!IsFounder(lptr, cptr))
	{
		notice(n_ChanServ, lptr->nick,
		       "You must IDENTIFY as a founder before resetting the founder nickname");
		RecordCommand("%s: %s!%s@%s failed SET [%s] FOUNDER %s",
		              n_ChanServ,
		              lptr->nick,
		              lptr->username,
		              lptr->hostname,
		              cptr->name,
		              (ac < 4) ? "" : av[3]);

		return;
	}

	RecordCommand("%s: %s!%s@%s SET [%s] FOUNDER %s",
	              n_ChanServ,
	              lptr->nick,
	              lptr->username,
	              lptr->hostname,
	              cptr->name,
	              (ac < 4) ? "" : av[3]);

	if (ac < 4)
	{
		notice(n_ChanServ, lptr->nick,
		       "Syntax: \002SET <channel> FOUNDER <nickname>\002");
		notice(n_ChanServ, lptr->nick,
		       ERR_MORE_INFO,
		       n_ChanServ,
		       "SET FOUNDER");
		return;
	}

	if (!(fptr = GetLink(av[3])))
	{
		notice(n_ChanServ, lptr->nick,
		       ERR_NOT_REGGED,
		       av[3]);
		return;
	}

    if (fptr->flags & NS_NOADD)
    {
        notice(n_ChanServ, lptr->nick,
               "The nickname [\002%s\002] cannot be set founder", fptr->nick);
        return;
    }


	if (MinNickAge)
	{
		if (current_ts - fptr->created < MinNickAge &&
				!IsValidAdmin(lptr))
		{
			notice(n_ChanServ, lptr->nick,
					"The nickname [\002%s\002] must be older than \002%s\002 in order to be a founder",
					fptr->nick, timeago(MinNickAge, 3));
			return;
		}
	}

	RemoveFounderChannelFromNick(&fptr, cptr);

	if (cptr->founder)
	{
		struct NickInfo *oldnick = GetLink(cptr->founder);

		if (oldnick)
			RemoveFounderChannelFromNick(&oldnick, cptr);

		MyFree(cptr->founder);
	}

	AddFounderChannelToNick(&fptr, cptr);

	cptr->founder = MyStrdup(fptr->nick);


	notice(n_ChanServ, lptr->nick,
	       "The founder nickname for %s has been changed to [\002%s\002]",
	       cptr->name,
	       fptr->nick);
}
