slapi_attr_get_oid_copy( const Slapi_Attr *attr, char **oidp )
{
	if ( attr == NULL ) {
		return LDAP_PARAM_ERROR;
	}
	*oidp = attr->a_desc->ad_type->sat_oid;

	return LDAP_SUCCESS;
}
