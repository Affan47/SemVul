aci_list_map_rights(
	struct berval	*list )
{
	struct berval	bv;
	slap_access_t	mask;
	int		i;

	ACL_INIT( mask );
	for ( i = 0; acl_get_part( list, i, ',', &bv ) >= 0; i++ ) {
		if ( bv.bv_len <= 0 ) {
			continue;
		}

		switch ( *bv.bv_val ) {
		case 'x':


			ACL_PRIV_SET(mask, ACL_PRIV_AUTH);
			break;
		case 'd':


			ACL_PRIV_SET(mask, ACL_PRIV_DISCLOSE);
			break;
		case 'c':
			ACL_PRIV_SET(mask, ACL_PRIV_COMPARE);
			break;
		case 's':


			ACL_PRIV_SET(mask, ACL_PRIV_SEARCH);
			break;
		case 'r':
			ACL_PRIV_SET(mask, ACL_PRIV_READ);
			break;
		case 'w':
			ACL_PRIV_SET(mask, ACL_PRIV_WRITE);
			break;
		default:
			break;
		}

	}

	return mask;
}
