glue_access_allowed(
	Operation		*op,
	Entry			*e,
	AttributeDescription	*desc,
	struct berval		*val,
	slap_access_t		access,
	AccessControlState	*state,
	slap_mask_t		*maskp )
{
	BackendDB *b0, *be = glue_back_select( op->o_bd, &e->e_nname );
	int rc;

	if ( be == NULL || be == op->o_bd || be->bd_info->bi_access_allowed == NULL )
		return SLAP_CB_CONTINUE;

	b0 = op->o_bd;
	op->o_bd = be;
	rc = be->bd_info->bi_access_allowed ( op, e, desc, val, access, state, maskp );
	op->o_bd = b0;
	return rc;
}
