print_reference(
	LDAP *ld,
	LDAPMessage *reference )
{
	int rc;
	char **refs = NULL;
	LDAPControl **ctrls;

	if( ldif < 2 ) {
		printf(_("# search reference\n"));
	}

	rc = ldap_parse_reference( ld, reference, &refs, &ctrls, 0 );

	if( rc != LDAP_SUCCESS ) {
		tool_perror( "ldap_parse_reference", rc, NULL, NULL, NULL, NULL );
		tool_exit( ld, EXIT_FAILURE );
	}

	if( refs ) {
		int i;
		for( i=0; refs[i] != NULL; i++ ) {
			tool_write_ldif( ldif ? LDIF_PUT_COMMENT : LDIF_PUT_VALUE,
				"ref", refs[i], strlen(refs[i]) );
		}
		ber_memvfree( (void **) refs );
	}

	if( ctrls ) {
		tool_print_ctrls( ld, ctrls );
		ldap_controls_free( ctrls );
	}
}
