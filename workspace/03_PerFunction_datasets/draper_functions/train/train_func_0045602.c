mdb_index_param(
	Backend *be,
	AttributeDescription *desc,
	int ftype,
	MDB_dbi *dbip,
	slap_mask_t *maskp,
	struct berval *prefixp )
{
	AttrInfo *ai;
	slap_mask_t mask, type = 0;

	ai = mdb_index_mask( be, desc, prefixp );

	if ( !ai ) {
#ifdef MDB_MONITOR_IDX
		switch ( ftype ) {
		case LDAP_FILTER_PRESENT:
			type = SLAP_INDEX_PRESENT;
			break;
		case LDAP_FILTER_APPROX:
			type = SLAP_INDEX_APPROX;
			break;
		case LDAP_FILTER_EQUALITY:
			type = SLAP_INDEX_EQUALITY;
			break;
		case LDAP_FILTER_SUBSTRINGS:
			type = SLAP_INDEX_SUBSTR;
			break;
		default:
			return LDAP_INAPPROPRIATE_MATCHING;
		}
		mdb_monitor_idx_add( be->be_private, desc, type );
#endif

		return LDAP_INAPPROPRIATE_MATCHING;
	}
	mask = ai->ai_indexmask;

	switch( ftype ) {
	case LDAP_FILTER_PRESENT:
		type = SLAP_INDEX_PRESENT;
		if( IS_SLAP_INDEX( mask, SLAP_INDEX_PRESENT ) ) {
			*prefixp = presence_key[0];
			goto done;
		}
		break;

	case LDAP_FILTER_APPROX:
		type = SLAP_INDEX_APPROX;
		if ( desc->ad_type->sat_approx ) {
			if( IS_SLAP_INDEX( mask, SLAP_INDEX_APPROX ) ) {
				goto done;
			}
			break;
		}


	case LDAP_FILTER_EQUALITY:
		type = SLAP_INDEX_EQUALITY;
		if( IS_SLAP_INDEX( mask, SLAP_INDEX_EQUALITY ) ) {
			goto done;
		}
		break;

	case LDAP_FILTER_SUBSTRINGS:
		type = SLAP_INDEX_SUBSTR;
		if( IS_SLAP_INDEX( mask, SLAP_INDEX_SUBSTR ) ) {
			goto done;
		}
		break;

	default:
		return LDAP_OTHER;
	}

#ifdef MDB_MONITOR_IDX
	mdb_monitor_idx_add( be->be_private, desc, type );
#endif

	return LDAP_INAPPROPRIATE_MATCHING;

done:
	*dbip = ai->ai_dbi;
	*maskp = mask;
	return LDAP_SUCCESS;
}
