slapi_entry_attr_replace_sv( Slapi_Entry *e, const char *type, Slapi_Value **vals )
{
	AttributeDescription *ad = NULL;
	const char *text;
	int rc;
	BerVarray bv;

	rc = slap_str2ad( type, &ad, &text );
	if ( rc != LDAP_SUCCESS ) {
		return 0;
	}

	attr_delete( &e->e_attrs, ad );

	rc = bvptr2obj( vals, &bv, NULL );
	if ( rc != LDAP_SUCCESS ) {
		return -1;
	}

	rc = attr_merge_normalize( e, ad, bv, NULL );
	slapi_ch_free( (void **)&bv );
	if ( rc != LDAP_SUCCESS ) {
		return -1;
	}

	return 0;
}
