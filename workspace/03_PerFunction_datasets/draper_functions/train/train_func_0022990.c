slapi_attr_type_cmp( const char *t1, const char *t2, int opt )
{
	AttributeDescription *a1 = NULL;
	AttributeDescription *a2 = NULL;
	const char *text;
	int ret;

	if ( slap_str2ad( t1, &a1, &text ) != LDAP_SUCCESS ) {
		return -1;
	}

	if ( slap_str2ad( t2, &a2, &text ) != LDAP_SUCCESS ) {
		return 1;
	}

#define ad_base_cmp(l,r) (((l)->ad_type->sat_cname.bv_len < (r)->ad_type->sat_cname.bv_len) \
	? -1 : (((l)->ad_type->sat_cname.bv_len > (r)->ad_type->sat_cname.bv_len) \
		? 1 : strcasecmp((l)->ad_type->sat_cname.bv_val, (r)->ad_type->sat_cname.bv_val )))

	switch ( opt ) {
	case SLAPI_TYPE_CMP_EXACT:
		ret = ad_cmp( a1, a2 );
		break;
	case SLAPI_TYPE_CMP_BASE:
		ret = ad_base_cmp( a1, a2 );
		break;
	case SLAPI_TYPE_CMP_SUBTYPE:
		ret = is_ad_subtype( a2, a2 );
		break;
	default:
		ret = -1;
		break;
	}

	return ret;
}
