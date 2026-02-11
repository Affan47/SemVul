tool_perror(
	const char *func,
	int err,
	const char *extra,
	const char *matched,
	const char *info,
	char **refs )
{
	fprintf( stderr, "%s: %s (%d)%s\n",
		func, ldap_err2string( err ), err, extra ? extra : "" );

	if ( matched && *matched ) {
		fprintf( stderr, _("\tmatched DN: %s\n"), matched );
	}

	if ( info && *info ) {
		fprintf( stderr, _("\tadditional info: %s\n"), info );
	}

	if ( refs && *refs ) {
		int i;
		fprintf( stderr, _("\treferrals:\n") );
		for( i=0; refs[i]; i++ ) {
			fprintf( stderr, "\t\t%s\n", refs[i] );
		}
	}
}
