main(int ac, char **av)
{
	int     c;

	while ((c = getopt_long(ac, av, "?st:hV", long_options, 0)) != EOF)
	{
		switch (c)
		{
			case 's':
				silent = 1;
				break;
			case 't':
				if (signal(SIGALRM, alarm_handler) == SIG_ERR)
					error(EXIT_FAILURE, errno, "signal");
				timeout = str2int(optarg);
				break;
			case 'V':
				print_version();
				exit(EXIT_SUCCESS);
			case 'h':
				usage(EXIT_SUCCESS);
			default:
				usage(EXIT_FAILURE);
		}
	}
	ac -= optind;
	av += optind;
	if (ac <= 0)
		usage(EXIT_FAILURE);

	while (ac--)
	{
		const char *name = *(av++);
		in_46_addr dst;

		if (inet_pton(AF_INET, name, &dst) > 0)
			resolve_addr4(name, &dst.in4);
		else if (inet_pton(AF_INET6, name, &dst) > 0)
			resolve_addr6(name, &dst.in6);
		else
			resolve_name(name);
	}

	return status;
}
