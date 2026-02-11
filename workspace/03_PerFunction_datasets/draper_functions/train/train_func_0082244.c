attrcrypt_keymgmt_store_key(ldbm_instance *li, attrcrypt_cipher_state *acs, SECKEYPublicKey *public_key, PK11SymKey *key_to_store)
{
	int ret = 0;
	SECItem wrapped_symmetric_key = {0};
	LDAPDebug(LDAP_DEBUG_TRACE,"-> attrcrypt_keymgmt_store_key\n", 0, 0, 0);

	ret = attrcrypt_wrap_key(acs, key_to_store, public_key, &wrapped_symmetric_key);
	if (!ret) {

		Slapi_Entry *e = NULL;
		Slapi_PBlock *pb = slapi_pblock_new();
		Slapi_Value *key_value = NULL;
		struct berval key_as_berval = {0};
		int rc = 0;
		char *entry_template =
			"dn: cn=%s,cn=encrypted attribute keys,cn=%s,cn=ldbm database,cn=plugins,cn=config\n"
			"objectclass:top\n"
    			"objectclass:extensibleObject\n"
    			"cn:%s\n";
		char *instance_name =  li->inst_name;
		char *entry_string = slapi_ch_smprintf(entry_template,acs->ace->cipher_display_name,instance_name,acs->ace->cipher_display_name);
		e = slapi_str2entry(entry_string, 0);

		key_as_berval.bv_val = (char *)wrapped_symmetric_key.data;
		key_as_berval.bv_len = wrapped_symmetric_key.len;
		key_value = slapi_value_new_berval(&key_as_berval);

		slapi_ch_free_string((char **)&wrapped_symmetric_key.data);
		slapi_entry_add_value(e, KEY_ATTRIBUTE_NAME, key_value);
		slapi_value_free(&key_value);

		slapi_add_entry_internal_set_pb(pb, e, NULL, li->inst_li->li_identity, 0);
		rc = slapi_add_internal_pb(pb);
		slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &rc);
		if (rc != LDAP_SUCCESS) {
			char *resulttext = NULL;
			slapi_pblock_get(pb, SLAPI_PB_RESULT_TEXT, &resulttext);
			LDAPDebug(LDAP_DEBUG_ANY, "attrcrypt_keymgmt_store_key: failed to add config key entries to the DSE: %d: %s: %s\n", rc, ldap_err2string(rc), resulttext ? resulttext : "unknown");
			ret = -1;
		}
		slapi_ch_free((void**)&entry_string);
		slapi_pblock_destroy(pb);
	}
	LDAPDebug(LDAP_DEBUG_TRACE,"<- attrcrypt_keymgmt_store_key\n", 0, 0, 0);
	return ret;
}
