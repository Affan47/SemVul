ShowChannels(int ac, char *av[])

{
	long flags;
	int ii;
	struct ChanInfo *cptr;

	flags = parseargs(ac, av);

	if ((flags & SHOW_FILE) && Filename)
	{
		MyFree(ChanServDB);
		ChanServDB = MyStrdup(Filename);
	}

	InitData();

	fprintf(stderr, "\n");

	if (flags & SHOW_HELP)
	{
		fprintf(stderr,
		        "Usage: %s [-h|?] [-n] [-f file] [chan1 chan2 ...]\n" \
		        "-h/-?     : Display this help screen\n" \
		        "-n        : Display number of registered channels\n" \
		        "-f file   : Use \"file\" as channel database\n" \
		        "chan1 ... : Display information about specific channels\n" \
		        "\n" \
		        "If no channels are specified, the entire database will be\n" \
		        "printed. Detailed information will be shown for given channels.\n" \
		        "If -n is specified, ONLY the number of registered channels will\n" \
		        "be displayed.\n", av[0]);

		exit(EXIT_SUCCESS);
	}

	if (!(flags & SHOW_TOTALCOUNT))
	{


		if (flags & SHOW_DETAIL)
		{
			for (ii = ncidx; ii < ac; ii++)
			{
				if ((cptr = FindChan(av[ii])))
					DisplayChan(cptr, 1);
				else
					fprintf(stderr, "No such channel: %s\n", av[ii]);

				fprintf(stderr, "\n");
			}
		}
		else
		{


			fprintf(stderr,
			        "%-30s %-30s\n",
			        "Channel",
			        "Time Since Last Used");
			for (ii = 0; ii < CHANLIST_MAX; ii++)
			{
				for (cptr = chanlist[ii]; cptr; cptr = cptr->next)
					DisplayChan(cptr, 0);
			}

			fprintf(stderr, "\n");
		}
	}

	fprintf(stderr, "There are %d registered channels\n",
	        Network->TotalChans);
}
