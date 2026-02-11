handle_private_option( int i )
{
	switch ( i ) {
#if 0
		int crit;
		char *control, *cvalue;
	case 'E':
		if( protocol == LDAP_VERSION2 ) {
			fprintf( stderr, _("%s: -E incompatible with LDAPv%d\n"),
				prog, version );
			exit( EXIT_FAILURE );
		}


		crit = 0;
		cvalue = NULL;
		if( optarg[0] == '!' ) {
			crit = 1;
			optarg++;
		}

		control = strdup( optarg );
		if ( (cvalue = strchr( control, '=' )) != NULL ) {
			*cvalue++ = '\0';
		}
		fprintf( stderr, _("Invalid modrdn extension name: %s\n"), control );
		usage();
#endif

	case 'r':
		remove_old_RDN++;
		break;

	case 's':
		if( protocol == LDAP_VERSION2 ) {
			fprintf( stderr, _("%s: -X incompatible with LDAPv%d\n"),
				prog, protocol );
			exit( EXIT_FAILURE );
		}
		newSuperior = strdup( optarg );
		protocol = LDAP_VERSION3;
		break;

	default:
		return 0;
	}
	return 1;
}
