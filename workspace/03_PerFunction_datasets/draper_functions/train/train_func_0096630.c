e2_toolbar_toggle_button_get_state (gchar *action_name)
{
	gchar *hashkey = g_strconcat (action_name, ".", action_name, NULL);
	E2_ToggleData *data = g_hash_table_lookup (toggles_hash, hashkey);
	g_free (hashkey);
	return ((data != NULL) ? data->current_state : FALSE);
}
