get_params(struct opt_def *opt_defs, int argc, char **argv) {
	char optlst[256] = { '\0' };
	struct opt_def *opt_def_map[256];
	size_t optlst_idx = 0;
	struct opt_def *opt_l;
	int ch;

	memset( opt_def_map, 0, sizeof(opt_def_map) );

	for( opt_l = opt_defs; opt_l && opt_l->optchr; ++opt_l ) {
		if( opt_def_map[(unsigned)(opt_l->optchr)] != NULL )
			die( EINVAL, "duplicate option def for '%c'", opt_l->optchr );
		opt_def_map[(unsigned)(opt_l->optchr)] = opt_l;
		optlst[optlst_idx++] = opt_l->optchr;
		if( opt_l->opttype != opt_flag )
			optlst[optlst_idx++] = ':';
	}
	optlst[optlst_idx] = '\0';

	while( (ch = getopt(argc, argv, optlst)) >= 0 ) {
		if( ch >= 256 ) {
			die( EINVAL, "getopt error, rc = %d", ch );
		}
		if( opt_def_map[ch] != 0 ) {
			switch(opt_def_map[ch]->opttype) {
			case opt_flag:
				opt_def_map[ch]->optarg.b = true;
				break;

			case opt_bool:
				{
					unsigned tmp;
					if( 1 != sscanf( optarg, "%u", &tmp ) )
						die( EINVAL, "getopt: invalid argument for -%c: %s", ch, optarg );
					opt_def_map[ch]->optarg.b = tmp != 0;
				}

				break;

			case opt_signed:
				if( 1 != sscanf( optarg, "%ld", &opt_def_map[ch]->optarg.s ) )
					die( EINVAL, "getopt: invalid argument for -%c: %s", ch, optarg );

				break;

			case opt_unsigned:
				if( 1 != sscanf( optarg, "%lu", &opt_def_map[ch]->optarg.u ) )
					die( EINVAL, "getopt: invalid argument for -%c: %s", ch, optarg );

				break;

			case opt_str:
				opt_def_map[ch]->optarg.str = strdup(optarg);
				break;
			}
		}
		else {
			return ch;
		}
	}

	return 0;
}
