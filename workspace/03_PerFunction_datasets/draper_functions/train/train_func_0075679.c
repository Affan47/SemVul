es_join(struct Luser *lptr, int ac, char **av, int sockfd)

{
  struct Channel *chptr;
  struct ChanInfo *cptr;

  if (ac < 2)
    return;

  if (!(chptr = FindChannel(av[1])))
    {
	  notice(n_SeenServ, lptr->nick, "No such channel [\002%s\002]",
			  av[1]);
      return;
    }

	if ((cptr = FindChan(chptr->name)))
	{
		if (IsFounder(lptr, cptr) || IsAdmin(lptr))
			cptr->flags |= CS_SEENSERV;
		else
		{
			notice(n_SeenServ, lptr->nick,
					"You are not the FOUNDER of [\002%s\002]",
					cptr->name);
			return;
		}
	}
	else
	{
		if (!IsAdmin(lptr))
		{
			notice(n_SeenServ, lptr->nick,
					"The channel [\002%s\002] is not registered",
					chptr->name);
			return;
		}
	}

	ss_join(chptr);
}
