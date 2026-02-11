attr_delete(
    Attribute	**attrs,
	AttributeDescription *desc )
{
	Attribute	**a;

	for ( a = attrs; *a != NULL; a = &(*a)->a_next ) {
		if ( (*a)->a_desc == desc ) {
			Attribute	*save = *a;
			*a = (*a)->a_next;
			attr_free( save );

			return LDAP_SUCCESS;
		}
	}

	return LDAP_NO_SUCH_ATTRIBUTE;
}
