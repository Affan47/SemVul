hs_givehelp(struct Luser *lptr, int ac, char **av)

{
	struct Luser *serviceptr;

	if (!irccmp(av[0], "HELP"))
	{
		if (ac >= 2)
			GiveHelp(n_HelpServ, lptr->nick, av[1], NODCC);
		else
			GiveHelp(n_HelpServ, lptr->nick, NULL, NODCC);
	}
	else
	{
		char  str[MAXLINE + 1];

		if (!(serviceptr = GetService(av[0])))
		{


			notice(n_HelpServ, lptr->nick,
			       "[\002%s\002] is an invalid service nickname",
			       av[0]);
			return;
		}

		if (ac < 2)
			strlcpy(str, "HELP", sizeof(str));
		else if (ac >= 3)
		{
			ircsprintf(str, "HELP %s %s", av[1], av[2]);
		}
		else
		{
			ircsprintf(str, "HELP %s", av[1]);
		}

		if (serviceptr == Me.osptr)
			os_process(lptr->nick, str, NODCC);

#ifdef NICKSERVICES

		if (serviceptr == Me.nsptr)
			ns_process(lptr->nick, str);

#ifdef CHANNELSERVICES

		if (serviceptr == Me.csptr)
			cs_process(lptr->nick, str);
#endif

#ifdef MEMOSERVICES

		if (serviceptr == Me.msptr)
			ms_process(lptr->nick, str);
#endif

#endif

#ifdef STATSERVICES

		if (serviceptr == Me.ssptr)
			ss_process(lptr->nick, str);

#endif

#ifdef SEENSERVICES

		if (serviceptr == Me.esptr)
			es_process(lptr->nick, str);

#endif

#ifdef GLOBALSERVICES

		if (serviceptr == Me.gsptr)
			gs_process(lptr->nick, str);

#endif

	}
}
