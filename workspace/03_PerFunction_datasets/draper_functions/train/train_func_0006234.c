s_part(int ac, char **av)

{
	char *who;

	if (ac < 3)
		return;

	if (av[0][0] == ':')
		who = av[0] + 1;
	else
		who = av[0];

	RemoveFromChannel(FindChannel(av[2]), FindClient(who));
}
