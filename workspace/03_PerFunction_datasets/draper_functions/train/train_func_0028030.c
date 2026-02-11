do_onethread( void *arg )
{
	int		i, j, thisconn;
	LDAP		**mlds;
	char		thrstr[BUFSIZ];
	int		rc, refcnt = 0;
	int		idx = (ldap_pvt_thread_t *)arg - rtid;

	mlds = (LDAP **) calloc( sizeof(LDAP *), noconns);
	if (mlds == NULL) {
		thread_error( idx, "Memory error: thread calloc for noconns" );
		exit( EXIT_FAILURE );
	}

	for ( j = 0; j < outerloops; j++ ) {
		for(i = 0; i < noconns; i++) {
			mlds[i] = ldap_dup(lds[i]);
			if (mlds[i] == NULL) {
				thread_error( idx, "ldap_dup error" );
			}
		}
		rc = ldap_get_option(mlds[0], LDAP_OPT_SESSION_REFCNT, &refcnt);
		snprintf(thrstr, BUFSIZ,
			"RO Thread conns: %d refcnt: %d (rc = %d)",
			noconns, refcnt, rc);
		thread_verbose(idx, thrstr);

		thisconn = (idx + j) % noconns;
		if (thisconn < 0 || thisconn >= noconns)
			thisconn = 0;
		if (mlds[thisconn] == NULL) {
			thread_error( idx, "(failed to dup)");
			tester_perror( "ldap_dup", "(failed to dup)" );
			exit( EXIT_FAILURE );
		}
		snprintf(thrstr, BUFSIZ, "Using conn %d", thisconn);
		thread_verbose(idx, thrstr);
		if ( filter != NULL ) {
			if (strchr(filter, '['))
				do_random2( mlds[thisconn], entry, filter, attrs,
					noattrs, nobind, loops, retries, delay, force,
					chaserefs, idx );
			else
				do_random( mlds[thisconn], entry, filter, attrs,
					noattrs, nobind, loops, retries, delay, force,
					chaserefs, idx );

		} else {
			do_read( mlds[thisconn], entry, attrs,
				noattrs, nobind, loops, retries, delay, force,
				chaserefs, idx );
		}
		for(i = 0; i < noconns; i++) {
			(void) ldap_destroy(mlds[i]);
			mlds[i] = NULL;
		}
	}
	free( mlds );
	return( NULL );
}
