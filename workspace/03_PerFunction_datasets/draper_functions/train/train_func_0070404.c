slap_sasl_check_authz( Operation *op,
	struct berval *searchDN,
	struct berval *assertDN,
	AttributeDescription *ad,
	struct berval *authc )
{
	int		rc,
			do_not_cache = op->o_do_not_cache;
	BerVarray	vals = NULL;

	Debug( LDAP_DEBUG_TRACE,
	   "==>slap_sasl_check_authz: does %s match %s rule in %s?\n",
	   assertDN->bv_val, ad->ad_cname.bv_val, searchDN->bv_val);


	op->o_do_not_cache = 1;
	rc = backend_attribute( op, NULL, searchDN, ad, &vals, ACL_AUTH );
	op->o_do_not_cache = do_not_cache;
	if( rc != LDAP_SUCCESS ) goto COMPLETE;


	rc = slap_sasl_matches( op, vals, assertDN, authc );

COMPLETE:
	if( vals ) ber_bvarray_free_x( vals, op->o_tmpmemctx );

	Debug( LDAP_DEBUG_TRACE,
	   "<==slap_sasl_check_authz: %s check returning %d\n",
		ad->ad_cname.bv_val, rc, 0);

	return( rc );
}
