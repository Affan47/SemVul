test_new_null (void)
{
	LDAPMod *mod;

	mod = _adcli_ldap_mod_new (LDAP_MOD_ADD, "test", NULL);
	assert (mod != NULL);

	assert (mod->mod_op == LDAP_MOD_ADD);
	assert_str_eq (mod->mod_type, "test");
	assert_num_eq (seq_count (mod->mod_vals.modv_strvals), 0);
	assert (mod->mod_vals.modv_strvals == NULL);

	_adcli_ldap_mod_free (mod);
}
