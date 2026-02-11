slapi_entry_add_value(Slapi_Entry *e, const char *type, const Slapi_Value *value)
{
	AttributeDescription	*ad = NULL;
	int 			rc;
	const char		*text;

	rc = slap_str2ad( type, &ad, &text );
	if ( rc != LDAP_SUCCESS ) {
		return -1;
	}

	rc = attr_merge_normalize_one( e, ad, (Slapi_Value *)value, NULL );
	if ( rc != LDAP_SUCCESS ) {
		return -1;
	}

	return 0;
}
