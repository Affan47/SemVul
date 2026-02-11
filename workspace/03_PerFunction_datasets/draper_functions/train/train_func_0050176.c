handle_private_option( int i )
{
	char	*control, *cvalue;
	int		crit;

	switch ( i ) {
	case 'E':
		if( protocol == LDAP_VERSION2 ) {
			fprintf( stderr, _("%s: -E incompatible with LDAPv%d\n"),
				prog, protocol );
			exit( EXIT_FAILURE );
		}


		crit = 0;
		cvalue = NULL;
		if( optarg[0] == '!' ) {
			crit = 1;
			optarg++;
		}

		control = ber_strdup( optarg );
		if ( (cvalue = strchr( control, '=' )) != NULL ) {
			*cvalue++ = '\0';
		}

#ifdef LDAP_CONTROL_DONTUSECOPY
		if ( strcasecmp( control, "dontUseCopy" ) == 0 ) {
			if( dontUseCopy ) {
				fprintf( stderr,
					_("dontUseCopy control previously specified\n"));
				exit( EXIT_FAILURE );
			}
			if( cvalue != NULL ) {
				fprintf( stderr,
					_("dontUseCopy: no control value expected\n") );
				usage();
			}
			if( !crit ) {
				fprintf( stderr,
					_("dontUseCopy: critical flag required\n") );
				usage();
			}

			dontUseCopy = 1 + crit;
		} else
#endif
		{
			fprintf( stderr,
				_("Invalid compare extension name: %s\n"), control );
			usage();
		}
		break;

	case 'z':
		quiet = 1;
		break;

	default:
		return 0;
	}
	return 1;
}
