slapi_build_control_from_berval( char *oid, struct berval *bvp,
	char iscritical, LDAPControl **ctrlp )
{
	int return_value = LDAP_SUCCESS;


	*ctrlp = (LDAPControl *)slapi_ch_calloc( 1, sizeof(LDAPControl));


	(*ctrlp)->ldctl_iscritical = iscritical;
	(*ctrlp)->ldctl_oid = slapi_ch_strdup( oid );
	if ( NULL == bvp ) {
		(*ctrlp)->ldctl_value.bv_len = 0;
		(*ctrlp)->ldctl_value.bv_val = NULL;
	} else {
		(*ctrlp)->ldctl_value = *bvp;
	}

	return return_value;
}
