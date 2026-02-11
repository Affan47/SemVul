c_set_forget(struct Luser *lptr, struct NickInfo *nptr, int ac, char **av)

{
	struct ChanInfo *cptr;

	if (!(cptr = FindChan(av[1])))
		return;

	if (!IsFounder(lptr, cptr))
	{
		notice(n_ChanServ, lptr->nick,
		       "Founder access is required for [\002SET FORGET\002]");
		RecordCommand("%s: %s!%s@%s failed SET [%s] FORGET %s",
		              n_ChanServ,
		              lptr->nick,
		              lptr->username,
		              lptr->hostname,
		              cptr->name,
		              (ac < 4) ? "" : StrToupper(av[3]));
		return;
	}

	RecordCommand("%s: %s!%s@%s SET [%s] FORGET %s",
	              n_ChanServ,
	              lptr->nick,
	              lptr->username,
	              lptr->hostname,
	              cptr->name,
	              (ac < 4) ? "" : StrToupper(av[3]));

	if (ac < 4)
	{
		notice(n_ChanServ, lptr->nick,
		       "Forgotten for channel %s is [\002%s\002]",
		       cptr->name,
		       (cptr->flags & CS_FORGET) ? "ON" : "OFF");
		return;
	}

	if (!irccmp(av[3], "ON"))
	{
		cptr->flags |= CS_FORGET;
		notice(n_ChanServ, lptr->nick,
		       "Toggled Forgotten for channel %s [\002ON\002]",
		       cptr->name);

		if (cs_ShouldBeOnChan(cptr))
			cs_part(FindChannel(cptr->name));

		return;
	}

	if (!irccmp(av[3], "OFF"))
	{
		cptr->flags &= ~CS_FORGET;
		notice(n_ChanServ, lptr->nick,
		       "Toggled Forgotten for channel %s [\002OFF\002]",
		       cptr->name);
		return;
	}


	notice(n_ChanServ, lptr->nick,
	       "Syntax: \002SET <channel> FORGET {ON|OFF}\002");
	notice(n_ChanServ, lptr->nick,
	       ERR_MORE_INFO,
	       n_ChanServ,
	       "SET FORGET");
}
