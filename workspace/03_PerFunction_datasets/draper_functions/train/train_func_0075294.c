ParseCmdline(int ARGC, char **ARGV)
{
	int c;
	int curindex=0;
	char  *ptr;
	extern char *optarg;
	extern int optind;

	if ( ARGC == 1 ) {
		usage(ARGV[0], 0, stdout);
	}

	while ((c = pgis_getopt(ARGC, ARGV, "kcdapDLs:Sg:iW:wIN:n")) != EOF){
		switch (c) {
			case 'c':
				if (opt == ' ')
					 opt ='c';
				else
					 return 0;
				break;
			case 'd':
				if (opt == ' ')
					 opt ='d';
				else
					 return 0;
				break;
			case 'a':
				if (opt == ' ')
					 opt ='a';
				else
					 return 0;
				break;
			case 'p':
				if (opt == ' ')
					 opt ='p';
				else
					 return 0;
				break;
			case 'D':
				dump_format =1;
				break;
                        case 'L':
                                sqlite_format=1;
                                break;
			case 'S':
				simple_geometries =1;
				break;
			case 's':
				(void)sscanf(optarg, "%d", &sr_id);
				break;
			case 'g':
				geom = optarg;
				break;
			case 'k':
				quoteidentifiers = 1;
				break;
			case 'i':
				forceint4 = 1;
				break;
			case 'I':
				createindex = 1;
				break;
			case 'w':
				hwgeom = 1;
				break;
			case 'n':
				readshape = 0;
				break;
			case 'W':
#ifdef HAVE_ICONV
				encoding = optarg;
#else
				fprintf(stderr, "WARNING: the -W switch will have no effect. UTF8 disabled at compile time\n");
#endif
				break;
			case 'N':
				switch (optarg[0])
				{
					case 'a':
						null_policy = abort_on_null;
						break;
					case 'i':
						null_policy = insert_null;
						break;
					case 's':
						null_policy = skip_null;
						break;
					default:
						fprintf(stderr, "Unsupported NULL geometry handling policy.\nValid policies: insert, skip, abort\n");
						exit(1);
				}
				break;
			case '?':
				usage(ARGV[0], 0, stdout);
			default:
				return 0;
		}
	}

	if ( !sr_id ) sr_id = -1;

	if ( !geom ) geom = "the_geom";

	if ( opt==' ' ) opt = 'c';

	for (; optind < ARGC; optind++){
		if(curindex ==0){
			shp_file = ARGV[optind];
		}else if(curindex == 1){
			table = ARGV[optind];
			if ( (ptr=strchr(table, '.')) )
			{
				*ptr = '\0';
				schema = table;
				table = ptr+1;
			}
		}
		curindex++;
	}


	if(curindex < 2 || curindex > 3){
		return 0;
	}


	if ( ! quoteidentifiers )
	{
		LowerCase(table);
		if ( schema ) LowerCase(schema);
	}

	return 1;
}
