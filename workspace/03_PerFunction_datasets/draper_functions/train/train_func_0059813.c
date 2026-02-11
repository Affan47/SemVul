getargs(int argc, char **argv)
{
	register int i;
	register char *s;

	if (argc > 0)
		myname = argv[0];

	for (i = 1; i < argc; ++i)
	{
		s = argv[i];
		if (*s != '-')
			break;

		switch (*++s)
		{
		case '\0':
			input_file = stdin;
			if (i + 1 < argc)
				usage();
			return;

		case '-':
			++i;
			no_more_options(i, argc, argv);
			return;

		case 'b':
			if (*++s)
				file_prefix = s;
			else if (++i < argc)
				file_prefix = argv[i];
			else
				usage();
			continue;

		case 'd':
			dflag = 1;
			break;

		case 'D':

			{
				char **ps;
				char *var_name = s + 1;
				extern char *defd_vars[];
				for (ps = &defd_vars[0]; *ps; ps++)
				{
					if (strcmp(*ps, var_name) == 0) {
						error(lineno, 0, 0, "Preprocessor variable %s already defined", var_name);
					}
				}
				*ps = MALLOC(strlen(var_name)+1);
				strcpy(*ps, var_name);
				*++ps = NULL;
			}
			continue;

		case 'E':
			Eflag = 1;
			break;

		case 'l':
			lflag = 1;
			break;

		case 'r':
			rflag = 1;
			break;

		case 't':
			tflag = 1;
			break;

		case 'v':
			vflag = 1;
			break;

		case 'S':
			if (*++s)
				read_skel(s);
			else if (++i < argc)
				read_skel(argv[i]);
			else
				usage();
			continue;

		default:
			usage();
		}

		for (;*++s;)
		{
			switch (*s)
			{


			case 'd':
				dflag = 1;
				break;

			case 'l':
				lflag = 1;
				break;

			case 'r':
				rflag = 1;
				break;

			case 't':
				tflag = 1;
				break;

			case 'v':
				vflag = 1;
				break;

			default:
				usage();
			}
		}

	}

	no_more_options(i, argc, argv);
}
