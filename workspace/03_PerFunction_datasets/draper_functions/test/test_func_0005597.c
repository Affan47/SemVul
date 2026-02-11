mr_schema_info( Entry *e )
{
	AttributeDescription *ad_matchingRules = slap_schema.si_ad_matchingRules;
	MatchingRule *mr;
	struct berval nval;

	LDAP_SLIST_FOREACH(mr, &mr_list, smr_next ) {
		if ( mr->smr_usage & SLAP_MR_HIDE ) {

			continue;
		}

		if ( ! mr->smr_match ) {

			continue;
		}

		if ( mr->smr_str.bv_val == NULL ) {
			if ( ldap_matchingrule2bv( &mr->smr_mrule, &mr->smr_str ) == NULL ) {
				return -1;
			}
		}
#if 0
		Debug( LDAP_DEBUG_TRACE, "Merging mr [%lu] %s\n",
			mr->smr_str.bv_len, mr->smr_str.bv_val, 0 );
#endif

		nval.bv_val = mr->smr_oid;
		nval.bv_len = strlen(mr->smr_oid);
		if( attr_merge_one( e, ad_matchingRules, &mr->smr_str, &nval ) ) {
			return -1;
		}
	}
	return 0;
}
