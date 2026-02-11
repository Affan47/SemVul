dynlist_is_dynlist_next( Operation *op, SlapReply *rs, dynlist_info_t *old_dli )
{
	slap_overinst	*on = (slap_overinst *)op->o_bd->bd_info;
	dynlist_info_t	*dli;

	Attribute	*a;

	if ( old_dli == NULL ) {
		dli = (dynlist_info_t *)on->on_bi.bi_private;

	} else {
		dli = old_dli->dli_next;
	}

	a = attrs_find( rs->sr_entry->e_attrs, slap_schema.si_ad_objectClass );
	if ( a == NULL ) {


		return NULL;
	}

	for ( ; dli; dli = dli->dli_next ) {
		if ( dli->dli_lud != NULL ) {

			if ( !BER_BVISNULL( &dli->dli_uri_nbase )
				&& !dnIsSuffixScope( &rs->sr_entry->e_nname,
					&dli->dli_uri_nbase,
					dli->dli_lud->lud_scope ) )
			{
				continue;
			}


			if ( dli->dli_uri_filter && test_filter( op, rs->sr_entry, dli->dli_uri_filter ) != LDAP_COMPARE_TRUE ) {
				continue;
			}
		}

		if ( attr_valfind( a,
				SLAP_MR_ATTRIBUTE_VALUE_NORMALIZED_MATCH |
				SLAP_MR_ASSERTED_VALUE_NORMALIZED_MATCH,
				&dli->dli_oc->soc_cname, NULL,
				op->o_tmpmemctx ) == 0 )
		{
			return dli;
		}
	}

	return NULL;
}
