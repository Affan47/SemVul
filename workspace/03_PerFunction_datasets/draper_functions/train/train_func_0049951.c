match_long_option ( int argc, char * const argv[],
			       const char *opttext,
			       const struct option *longopt, int *option ) {
	size_t optlen;
	const char *argument = NULL;


	optlen = strlen ( longopt->name );
	if ( strncmp ( opttext, longopt->name, optlen ) != 0 )
		return 0;


	if ( opttext[optlen] == '=' ) {
		argument = &opttext[ optlen + 1 ];
	} else if ( opttext[optlen] ) {

		return 0;
	}


	optind++;


	if ( ( longopt->has_arg != no_argument ) && ( ! argument ) )
		argument = get_argv_argument ( argc, argv );


	if ( ( longopt->has_arg == required_argument ) && ( ! argument ) ) {
		printf ( "Option \"%s\" requires an argument\n",
			 longopt->name );
		*option = ':';
		return 1;
	}


	if ( ( longopt->has_arg == no_argument ) && argument ) {
		printf ( "Option \"%s\" takes no argument\n", longopt->name );
		*option = ':';
		return 1;
	}


	optarg = ( char * ) argument;
	if ( longopt->flag ) {
		*(longopt->flag) = longopt->val;
		*option = 0;
	} else {
		*option = longopt->val;
	}
	return 1;
}
