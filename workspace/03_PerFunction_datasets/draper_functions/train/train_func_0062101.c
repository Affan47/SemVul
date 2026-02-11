windows_unsync_entry(Private_Repl_Protocol *prp, Slapi_Entry *e)
{


	Slapi_Mods *smods = NULL;
	Slapi_Value *ntu = NULL, *ntg = NULL;
	Slapi_Value *va[2] = {NULL, NULL};
	char **syncattrs = NULL;
	PRUint32 ocflags = SLAPI_OC_FLAG_REQUIRED|SLAPI_OC_FLAG_ALLOWED;
	Slapi_PBlock *pb = NULL;
	int ii;
	int rc = -1;

	smods = slapi_mods_new();
	ntu = slapi_value_new_string("ntuser");
	ntg = slapi_value_new_string("ntgroup");

	if (slapi_entry_attr_has_syntax_value(e, "objectclass", ntu)) {
		syncattrs = slapi_schema_list_objectclass_attributes(slapi_value_get_string(ntu), ocflags);
		va[0] = ntu;
	} else if (slapi_entry_attr_has_syntax_value(e, "objectclass", ntg)) {
		syncattrs = slapi_schema_list_objectclass_attributes(slapi_value_get_string(ntg), ocflags);
		va[0] = ntg;
	} else {
		rc = 0;
		goto done;
	}
	slapi_mods_add_mod_values(smods, LDAP_MOD_DELETE, "objectclass", va);
	slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
					"%s: windows_unsync_entry: removing objectclass %s from %s\n",
					agmt_get_long_name(prp->agmt), slapi_value_get_string(va[0]),
					slapi_entry_get_dn_const(e));

	for (ii = 0; syncattrs && syncattrs[ii]; ++ii) {
		const char *type = syncattrs[ii];
		Slapi_Attr *attr = NULL;

		if (!slapi_entry_attr_find(e, type, &attr) && attr) {
			if (!PL_strncasecmp(type, "nt", 2)) {
				slapi_mods_add_mod_values(smods, LDAP_MOD_DELETE, type, NULL);
				slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
								"%s: windows_unsync_entry: removing attribute %s from %s\n",
								agmt_get_long_name(prp->agmt), type,
								slapi_entry_get_dn_const(e));
			}
		}
	}

	pb = slapi_pblock_new();
	if (!pb) {
		goto done;
	}
	slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
					"%s: windows_unsync_entry: modifying entry %s\n",
					agmt_get_long_name(prp->agmt), slapi_entry_get_dn_const(e));
	slapi_modify_internal_set_pb_ext(pb, slapi_entry_get_sdn(e),
									 slapi_mods_get_ldapmods_byref(smods), NULL, NULL,
									 repl_get_plugin_identity (PLUGIN_MULTIMASTER_REPLICATION), 0);
	slapi_modify_internal_pb(pb);
	slapi_pblock_get (pb, SLAPI_PLUGIN_INTOP_RESULT, &rc);
	if (rc) {
		slapi_log_error(SLAPI_LOG_FATAL, windows_repl_plugin_name,
						"%s: windows_unsync_entry: failed to modify entry %s - error %d:%s\n",
						agmt_get_long_name(prp->agmt), slapi_entry_get_dn_const(e),
						rc, ldap_err2string(rc));
	}
	slapi_pblock_destroy(pb);

done:
	slapi_ch_array_free(syncattrs);
	slapi_mods_free(&smods);
	slapi_value_free(&ntu);
	slapi_value_free(&ntg);

	return rc;
}
