compare_one_secret (NMSettingVPN *a,
                    NMSettingVPN *b,
                    NMSettingCompareFlags flags)
{
	GHashTable *a_secrets, *b_secrets;
	GHashTableIter iter;
	const char *key, *val;

	a_secrets = NM_SETTING_VPN_GET_PRIVATE (a)->secrets;
	b_secrets = NM_SETTING_VPN_GET_PRIVATE (b)->secrets;

	g_hash_table_iter_init (&iter, a_secrets);
	while (g_hash_table_iter_next (&iter, (gpointer) &key, (gpointer) &val)) {
		NMSettingSecretFlags a_secret_flags = NM_SETTING_SECRET_FLAG_NONE;
		NMSettingSecretFlags b_secret_flags = NM_SETTING_SECRET_FLAG_NONE;

		nm_setting_get_secret_flags (NM_SETTING (a), key, &a_secret_flags, NULL);
		nm_setting_get_secret_flags (NM_SETTING (b), key, &b_secret_flags, NULL);


		if (a_secret_flags != b_secret_flags)
			return FALSE;

		if (   (flags & NM_SETTING_COMPARE_FLAG_IGNORE_AGENT_OWNED_SECRETS)
		    && (a_secret_flags & NM_SETTING_SECRET_FLAG_AGENT_OWNED))
			continue;

		if (   (flags & NM_SETTING_COMPARE_FLAG_IGNORE_NOT_SAVED_SECRETS)
		    && (a_secret_flags & NM_SETTING_SECRET_FLAG_NOT_SAVED))
			continue;


		if (g_strcmp0 (val, nm_setting_vpn_get_secret (b, key)) != 0)
			return FALSE;
	}

	return TRUE;
}
