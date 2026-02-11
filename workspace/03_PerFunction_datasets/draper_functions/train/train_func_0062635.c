n_access_list(struct Luser *lptr, struct NickInfo *target, int ac, char **av)

{
	struct NickInfo *nptr;
	int cnt = 1;
	struct NickHost *hptr;
	char *mask;

	if (target)
		nptr = target;
	else
		nptr = GetLink(lptr->nick);

	if (!nptr)
		return;

	mask = NULL;

	if (target)
	{
		if (ac >= 4)
			mask = av[3];
	}
	else
	{
		if (ac >= 3)
			mask = av[2];
	}

	if (target)
		RecordCommand("%s: Administrator %s!%s@%s ACCESS %s LIST %s",
					  n_NickServ,
					  lptr->nick,
					  lptr->username,
					  lptr->hostname,
					  target->nick,
					  mask ? mask : "");
	else
		RecordCommand("%s: %s!%s@%s ACCESS LIST %s",
					  n_NickServ,
					  lptr->nick,
					  lptr->username,
					  lptr->hostname,
					  mask ? mask : "");

	notice(n_NickServ, lptr->nick,
		   "-- Access List for [\002%s\002] --",
		   nptr->nick);

	for (hptr = nptr->hosts; hptr; hptr = hptr->next)
	{
		if (mask)
			if (match(mask, hptr->hostmask) == 0)
				continue;

		notice(n_NickServ, lptr->nick, "%d) %s",
			   cnt++,
			   hptr->hostmask);
	}

	notice(n_NickServ, lptr->nick, "-- End of list --");
}
