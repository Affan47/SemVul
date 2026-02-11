clear_unsaved_secrets (GHashTableIter *iter,
                       NMSettingSecretFlags flags,
                       gpointer user_data)
{
	if (flags & (NM_SETTING_SECRET_FLAG_NOT_SAVED | NM_SETTING_SECRET_FLAG_NOT_REQUIRED))
		g_hash_table_iter_remove (iter);
	return TRUE;
}
