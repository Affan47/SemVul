pw_get_admin_users(passwdPolicy *pwp)
{
	Slapi_PBlock *pb = NULL;
	const Slapi_DN *sdn = pwp->pw_admin;
	char **uniquemember_vals = NULL;
	char **member_vals = NULL;
	const char *binddn = slapi_sdn_get_dn(sdn);
	int uniquemember_count = 0;
	int member_count = 0;
	int nentries = 0;
	int count = 0;
	int res;
	int i;

	if(binddn == NULL){
		return;
	}


	pb = slapi_pblock_new();
	slapi_search_internal_set_pb(pb, binddn, LDAP_SCOPE_BASE,"(|(objectclass=groupofuniquenames)(objectclass=groupofnames))",
		NULL, 0, NULL, NULL, (void *) plugin_get_default_component_id(), 0);
	slapi_search_internal_pb(pb);
	slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &res);
	if (res != LDAP_SUCCESS) {
		slapi_pblock_destroy(pb);
		LDAPDebug(LDAP_DEBUG_ANY, "pw_get_admin_users: search failed for %s: error %d - Password Policy Administrators can not be set\n",
			slapi_sdn_get_dn(sdn), res, 0);
		return;
	}


	slapi_pblock_get(pb, SLAPI_NENTRIES, &nentries);
	if ( nentries > 0 ){


		Slapi_Entry **entries = NULL;

		slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_SEARCH_ENTRIES, &entries);
		uniquemember_vals = slapi_entry_attr_get_charray_ext(entries[0], "uniquemember", &uniquemember_count);
		member_vals = slapi_entry_attr_get_charray_ext(entries[0], "member", &member_count);
		pwp->pw_admin_user = (Slapi_DN **)slapi_ch_calloc((uniquemember_count + member_count + 1), sizeof(Slapi_DN *));
		if(uniquemember_count > 0){
			for(i = 0; i < uniquemember_count; i++){
				pwp->pw_admin_user[count++] = slapi_sdn_new_dn_passin(uniquemember_vals[i]);
			}
		}
		if(member_count > 0){
			for(i = 0; i < member_count; i++){
				pwp->pw_admin_user[count++] = slapi_sdn_new_dn_passin(member_vals[i]);
			}
		}
		slapi_ch_free((void**)&uniquemember_vals);
		slapi_ch_free((void**)&member_vals);
	} else {

		pwp->pw_admin_user = (Slapi_DN **)slapi_ch_calloc(2, sizeof(Slapi_DN *));
		pwp->pw_admin_user[0] = slapi_sdn_dup(sdn);
	}
	slapi_free_search_results_internal(pb);
	slapi_pblock_destroy(pb);
}
