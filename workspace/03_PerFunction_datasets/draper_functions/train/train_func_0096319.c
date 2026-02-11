aclinit_search_and_update_aci ( int thisbeonly, const Slapi_DN *base,
								char *be_name, int scope, int op,
								acl_lock_flag_t lock_flag )
{
	char				*attrs[2] = { "aci", NULL };

	Slapi_PBlock 	*aPb;
	LDAPControl		**ctrls=NULL;
	struct berval	*bval;
	aclinit_handler_callback_data_t call_back_data;

	PR_ASSERT( lock_flag == DONT_TAKE_ACLCACHE_WRITELOCK ||
				lock_flag == DO_TAKE_ACLCACHE_WRITELOCK);

	if ( thisbeonly && be_name == NULL) {
		slapi_log_error ( SLAPI_LOG_FATAL, plugin_name,
						"Error: This  be_name must be specified.\n");
		return -1;
	}


	aPb = slapi_pblock_new ();


	if ( thisbeonly ) {

		bval = (struct berval *)slapi_ch_malloc(sizeof(struct berval));
		bval->bv_len = strlen(be_name) + 1;
		bval->bv_val = slapi_ch_strdup(be_name);

		ctrls = (LDAPControl **)slapi_ch_calloc( 2, sizeof(LDAPControl *));
		ctrls[0] = NULL;
		ctrls[1] = NULL;

		slapi_build_control_from_berval(
										MTN_CONTROL_USE_ONE_BACKEND_OID,
                						bval,
										1 ,
										ctrls);

	}

	slapi_search_internal_set_pb (	aPb,
					slapi_sdn_get_dn(base),
					scope,
					"(|(aci=*)(objectclass=ldapsubentry))",
					attrs,
					0 ,
					ctrls ,
					NULL ,
					aclplugin_get_identity (ACL_PLUGIN_IDENTITY),
					SLAPI_OP_FLAG_NEVER_CHAIN );

	if (thisbeonly) {
		slapi_pblock_set(aPb, SLAPI_REQCONTROLS, ctrls);
	}

	call_back_data.op = op;
	call_back_data.retCode = 0;
	call_back_data.lock_flag = lock_flag;

	slapi_search_internal_callback_pb(aPb,
					  &call_back_data ,
					  NULL,
					  __aclinit_handler,
					  NULL );

	if (thisbeonly) {
		slapi_ch_free((void **)&bval);
	}


	slapi_pblock_destroy (aPb);

	return call_back_data.retCode;

}
