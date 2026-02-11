rootDseObjectClass (
	Backend *be,
	Entry *e,
	ObjectClass *oc,
	const char** text,
	char *textbuf, size_t textlen )
{
	*text = textbuf;

	if( e->e_nname.bv_len ) {
		snprintf( textbuf, textlen,
			"objectClass \"%s\" only allowed in the root DSE",
			oc->soc_oid );
		return LDAP_OBJECT_CLASS_VIOLATION;
	}


	assert( 0 );
	return LDAP_SUCCESS;
}
