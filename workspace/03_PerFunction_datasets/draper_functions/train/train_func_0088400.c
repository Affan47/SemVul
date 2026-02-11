es_loaddata()
{
	FILE *fp;
	char line[MAXLINE + 1], **av;
	char *keyword;
	int ac, ret = 1, cnt, type = 0;
	aSeen *seen;

	if ((fp = fopen(SeenServDB, "r")) == NULL)
	{

		return ( -1);
	}

	FreeSeen();
	cnt = 0;

	while (fgets(line, sizeof(line), fp))
	{
		cnt++;
		ac = SplitBuf(line, &av);
		if (!ac)
		{

			MyFree(av);
			continue;
		}

		if (av[0][0] == ';')
		{
			MyFree(av);
			continue;
		}

		if (!ircncmp("->", av[0], 2))
		{


			if (ac < 4)
			{
				fatal(1, "%s:%d Invalid database format (FATAL)", SeenServDB,
				      cnt);
				ret = -2;
				MyFree(av);
				continue;
			}

			keyword = av[0] + 2;
			type = 0;
			if (!ircncmp(keyword, "QUIT", 4))
			{
				type = 1;
			}
			else if (!ircncmp(keyword, "NICK", 4))
			{
				type = 2;
			}
			if (type)
			{
				seen = MyMalloc(sizeof(aSeen));
				memset(seen, 0, sizeof(aSeen));
				strlcpy(seen->nick, av[1], NICKLEN + 1);
				seen->userhost = MyStrdup(av[2]);
				seen->msg = (type == 1) ? MyStrdup(av[4] + 1) : NULL;
				seen->time = atol(av[3]);
				seen->type = type;
				seen->prev = seenp;
				seen->next = NULL;
				if (seenp)
					seenp->next = seen;
				seenp = seen;
				if (!seenb)
					seenb = seen;
				++seenc;
			}
		}

		MyFree(av);
	}

	fclose(fp);

	return (ret);
}
