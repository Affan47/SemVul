pid_parse(int *argc, char **argv)
{
	int		index = 0;
	int		othersc;
	char		**othersv;


	if (proclist == 0) {
		proclist = al_init(sizeof(struct id), 0);
		if (proclist == 0) return(LAMERROR);
	}


	othersc = 1;
	othersv = argv++;
	++othersv;
	--*argc;


	while (*argc) {


		if ((**argv == 'p') && isdigit((int) *(*argv + 1))) {

			if (id_range(*argv + 1, SELECT_PID, 1, &index,
				     proclist))
					return(LAMERROR);
		}


		else if (((**argv == '%') || (**argv == 'i')) &&
				isdigit((int) *(argv[0] + 1))) {

			if (id_range(*argv + 1, SELECT_INDEX, 1, &index,
					proclist)) return(LAMERROR);
		}


		else {
			*(othersv++) = *argv;
			++othersc;
		}

		--*argc;
		++argv;
	}

	*argc = othersc;
	return (0);
}
