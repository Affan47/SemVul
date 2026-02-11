add_password_attrs( Slapi_PBlock *pb, Operation *op, Slapi_Entry *e )
{
	struct berval   bv;
	struct berval   *bvals[2];
	Slapi_Attr     **a, **next;
	passwdPolicy *pwpolicy = NULL;
	const char *dn = slapi_entry_get_ndn(e);
	int has_allowchangetime = 0, has_expirationtime = 0;
	time_t existing_exptime = 0;

	LDAPDebug( LDAP_DEBUG_TRACE, "add_password_attrs\n", 0, 0, 0 );

	bvals[0] = &bv;
	bvals[1] = NULL;


	for ( a = &e->e_attrs; *a != NULL; a = next ) {
		if ( strcasecmp( (*a)->a_type,
			"passwordexpirationtime" ) == 0) {
			Slapi_Value *sval;
			if (slapi_attr_first_value(*a, &sval) == 0) {
				const struct berval *bv = slapi_value_get_berval(sval);
				existing_exptime = parse_genTime(bv->bv_val);
			}
			has_expirationtime = 1;

		} else if ( strcasecmp( (*a)->a_type,
			"passwordallowchangetime" ) == 0) {
			has_allowchangetime = 1;
		}
		next = &(*a)->a_next;
	}

	if ( has_allowchangetime && has_expirationtime ) {
		return;
	}

	pwpolicy = new_passwdPolicy(pb, dn);

	if ( !has_expirationtime &&
		( pwpolicy->pw_exp || pwpolicy->pw_must_change ) ) {
		if ( pwpolicy->pw_must_change) {

			bv.bv_val = format_genTime ( NO_TIME );
		} else if ( pwpolicy->pw_exp ) {
			bv.bv_val = format_genTime ( time_plus_sec ( current_time (),
       	                 pwpolicy->pw_maxage ) );
		}
		bv.bv_len = strlen( bv.bv_val );
		slapi_entry_attr_merge( e, "passwordexpirationtime", bvals );
		slapi_ch_free_string( &bv.bv_val );
	}


	if ( !has_allowchangetime && pwpolicy->pw_minage != 0 &&
		(has_expirationtime && existing_exptime > current_time()) ) {
		bv.bv_val = format_genTime ( time_plus_sec ( current_time (),
                        pwpolicy->pw_minage ) );
		bv.bv_len = strlen( bv.bv_val );

		slapi_entry_attr_merge( e, "passwordallowchangetime", bvals );
		slapi_ch_free((void **) &bv.bv_val );
	}
}
