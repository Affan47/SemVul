getopt_enh(int argc,
	       char **argv,
	       struct enh_options *eo,
	       int *longind,
	       int *mask,
	       char *userparams)
{
	int ch;
	char *s;
	int option_index;
	int ret=0;

	if ( !my_shortopts )
		parse_option_table(eo);

	while (1){
		option_index = -1;
		ch = getopt_long (argc, argv, my_shortopts, my_longopts,
				  & option_index);
		if ( ch == EOF )
			break;

		switch(ch){
		case 'h':
			print_usage(argv[0], eo, userparams);
			print_help(eo);
			exit(0);
		case '?':
			ret = 1;
			continue;
		}
		if ( option_index == -1 )

			for (option_index=0;
			     option_index < length &&
			     eo[option_index].shorto != (char) ch;
			     option_index++);

		if ( my_xopts[option_index] ){
			fprintf(stderr,"option %s given twice\n",
				eo[option_index].longo);
			ret = 1;
			continue;
		}

		if ( optarg )
			my_xopts[option_index] = optarg;
		else
			my_xopts[option_index] = argv[0];
		*mask |= eo[option_index].mask;

		if ( eo[option_index].type & EO_TYPE_DELAYED )
			continue;
		if ( eo[option_index].type == EO_TYPE_MANUAL ){
			if ( longind )
				*longind = option_index;
			return ch;
		}
		ret |= parse_option(eo+option_index, optarg);
	}


	if ( ret ){
		print_usage(argv[0], eo, userparams);
		return '?';
	} else
		return EOF;
}
