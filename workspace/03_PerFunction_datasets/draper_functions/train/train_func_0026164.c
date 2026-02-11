print_whatfailed( LDAP *ld, LDAPControl *ctrl )
{
	BerElement *ber;
	ber_tag_t tag;
	ber_len_t siz;
	BerVarray bva = NULL;


	ber = ber_init( &ctrl->ldctl_value );

	if ( ber == NULL ) {
		return LDAP_NO_MEMORY;
	}

	siz = sizeof(struct berval);
	tag = ber_scanf( ber, "[M]", &bva, &siz, 0 );
	if ( tag != LBER_ERROR ) {
		int i;

		tool_write_ldif( LDIF_PUT_COMMENT, " what failed:", NULL, 0 );

		for ( i = 0; bva[i].bv_val != NULL; i++ ) {
			tool_write_ldif( LDIF_PUT_COMMENT, NULL, bva[i].bv_val, bva[i].bv_len );
		}

		ldap_memfree( bva );
	}

        ber_free( ber, 1 );


	return 0;
}
