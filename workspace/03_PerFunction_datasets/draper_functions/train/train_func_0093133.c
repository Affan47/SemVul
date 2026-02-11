config_build_attrs( Entry *e, AttributeType **at, AttributeDescription *ad,
	ConfigTable *ct, ConfigArgs *c )
{
	int i, rc;

	for (; at && *at; at++) {

		if ((*at)->sat_ad == ad || (*at)->sat_ad == slap_schema.si_ad_cn )
			continue;
		for (i=0;ct[i].name;i++) {
			if (ct[i].ad == (*at)->sat_ad) {
				rc = config_get_vals(&ct[i], c);


				if (rc == LDAP_SUCCESS && c->rvalue_vals != NULL ) {
					if ( c->rvalue_nvals )
						rc = attr_merge(e, ct[i].ad, c->rvalue_vals,
							c->rvalue_nvals);
					else {
						slap_syntax_validate_func *validate =
							ct[i].ad->ad_type->sat_syntax->ssyn_validate;
						if ( validate ) {
							int j;
							for ( j=0; c->rvalue_vals[j].bv_val; j++ ) {
								rc = ordered_value_validate( ct[i].ad,
									&c->rvalue_vals[j], LDAP_MOD_ADD );
								if ( rc ) {
									Debug( LDAP_DEBUG_ANY,
										"config_build_attrs: error %d on %s value #%d\n",
										rc, ct[i].ad->ad_cname.bv_val, j );
									return rc;
								}
							}
						}

						rc = attr_merge_normalize(e, ct[i].ad,
							c->rvalue_vals, NULL);
					}
					ber_bvarray_free( c->rvalue_nvals );
					ber_bvarray_free( c->rvalue_vals );
					if ( rc ) {
						Debug( LDAP_DEBUG_ANY,
							"config_build_attrs: error %d on %s\n",
							rc, ct[i].ad->ad_cname.bv_val, 0 );
						return rc;
					}
				}
				break;
			}
		}
	}
	return 0;
}
