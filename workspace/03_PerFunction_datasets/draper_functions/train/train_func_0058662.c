ldif_tool_entry_put( BackendDB *be, Entry *e, struct berval *text )
{
	int rc;
	const char *errmsg = NULL;
	struct berval path;
	char *parentdir;
	Operation op = {0};

	op.o_bd = be;
	rc = ldif_prepare_create( &op, e, &path, &parentdir, &errmsg );
	if ( rc == LDAP_SUCCESS ) {
		rc = ldif_write_entry( &op, e, &path, parentdir, &errmsg );

		SLAP_FREE( path.bv_val );
		if ( parentdir != NULL )
			SLAP_FREE( parentdir );
		if ( rc == LDAP_SUCCESS )
			return 1;
	}

	if ( errmsg == NULL && rc != LDAP_OTHER )
		errmsg = ldap_err2string( rc );
	if ( errmsg != NULL )
		snprintf( text->bv_val, text->bv_len, "%s", errmsg );
	return NOID;
}
