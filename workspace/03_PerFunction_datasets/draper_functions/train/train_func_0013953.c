do_makedefs(options)
char	*options;
{
	boolean more_than_one;


	monst_init();
	objects_init();


	make_version();


	more_than_one = strlen(options) > 1;
	while (*options) {
	    if (more_than_one)
		Fprintf(stderr, "makedefs -%c\n", *options);

	    switch (*options) {
		case 'o':
		case 'O':	do_objs();
				break;
		case 'd':
		case 'D':	do_data();
				break;
		case 'e':
		case 'E':	do_dungeon();
				break;
		case 'm':
		case 'M':	do_monstr();
				break;
		case 'v':
		case 'V':	do_date();
				do_options();
				break;
		case 'p':
		case 'P':	do_permonst();
				break;
		case 'q':
		case 'Q':	do_questtxt();
				break;
		case 'r':
		case 'R':	do_rumors();
				break;
		case 'h':
		case 'H':	do_oracles();
				break;
		case 'z':
		case 'Z':	do_vision();
				break;

		default:	Fprintf(stderr,	"Unknown option '%c'.\n",
					*options);
				(void) fflush(stderr);
				exit(EXIT_FAILURE);

	    }
	    options++;
	}
	if (more_than_one) Fprintf(stderr, "Completed.\n");

}
