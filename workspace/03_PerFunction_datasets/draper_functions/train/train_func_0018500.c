glue_entry_get_rw (
	Operation		*op,
	struct berval	*dn,
	ObjectClass		*oc,
	AttributeDescription	*ad,
	int	rw,
	Entry	**e )
{
	int rc;
	BackendDB *b0 = op->o_bd;
	op->o_bd = glue_back_select( b0, dn );

	if ( op->o_bd->be_fetch ) {
		rc = op->o_bd->be_fetch( op, dn, oc, ad, rw, e );
	} else {
		rc = LDAP_UNWILLING_TO_PERFORM;
	}
	op->o_bd =b0;
	return rc;
}
