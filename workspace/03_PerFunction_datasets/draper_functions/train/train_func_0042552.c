load_bans (void)
{
    FILE   *fp;
    LIST   *list, **last = &Bans;
    BAN    *b;
    int     ac;
    char   *av[5], path[_POSIX_PATH_MAX];
    char   *banptr, realban[256];

    snprintf (path, sizeof (path), "%s/bans", Config_Dir);
    if (!(fp = fopen (path, "r")))
    {
	if (errno != ENOENT)
	    logerr ("load_bans", path);
	return -1;
    }
    while (fgets (Buf, sizeof (Buf) - 1, fp))
    {
	ac = split_line (av, FIELDS (av), Buf);
	if (ac < 1)
	    continue;
	b = CALLOC (1, sizeof (BAN));
	if (!b)
	{
	    OUTOFMEMORY ("load_bans");
	    fclose (fp);
	    return -1;
	}
	banptr = normalize_ban (av[0], realban, sizeof (realban));
	b->target = STRDUP (banptr);
	if (!b->target)
	{
	    OUTOFMEMORY ("load_bans");
	    FREE (b);
	    break;
	}
	if (ac >= 4)
	{
	    b->setby = STRDUP (av[1]);
	    b->when = atol (av[2]);
	    truncate_reason (av[3]);
	    b->reason = STRDUP (av[3]);
	    if (ac > 4)
		b->timeout = atoi (av[4]);
	}
	else
	{

	    b->setby = STRDUP (Server_Name);
	    b->reason = STRDUP ("");
	    b->when = global.current_time;
	}
	list = CALLOC (1, sizeof (LIST));
	if (!list)
	{
	    OUTOFMEMORY ("load_bans");
	    free_ban (b);
	    fclose (fp);
	    return -1;
	}
	list->data = b;

	*last = list;
	last = &list->next;
    }
    fclose (fp);
    return 0;
}
