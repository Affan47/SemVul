slapi_attr_type2plugin( const char *type, void **pi )
{
	char			buf[SLAPD_TYPICAL_ATTRIBUTE_NAME_MAX_LENGTH];
	char			*tmp, *basetype;
	int				rc;

	basetype = buf;
	if ( (tmp = slapi_attr_basetype( type, buf, sizeof(buf) )) != NULL ) {
		basetype = tmp;
	}
	rc = -1;
	*pi = attr_syntax_get_plugin_by_name_with_default( basetype );
	if ( NULL != *pi ) {
		rc = 0;
	}
	slapi_ch_free_string(&tmp);

	return( rc );
}
