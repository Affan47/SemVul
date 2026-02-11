rootDseAttribute (
	Backend *be,
	Entry *e,
	Attribute *attr,
	const char** text,
	char *textbuf, size_t textlen )
{
	*text = textbuf;

	if( e->e_nname.bv_len ) {
		snprintf( textbuf, textlen,
			"attribute \"%s\" only allowed in the root DSE",
			attr->a_desc->ad_cname.bv_val );
		return LDAP_OBJECT_CLASS_VIOLATION;
	}


	assert( 0 );
	return LDAP_SUCCESS;
}
