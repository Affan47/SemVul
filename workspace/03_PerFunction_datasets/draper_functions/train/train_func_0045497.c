process_group (GDataEntry *entry,
               guint entry_key,
               guint entry_count,
               EBookBackend *backend)
{
	EBookBackendGooglePrivate *priv;
	const gchar *uid, *system_group_id;
	gchar *name;
	gboolean is_deleted;

	priv = E_BOOK_BACKEND_GOOGLE_GET_PRIVATE (backend);

	g_debug (G_STRFUNC);
	uid = gdata_entry_get_id (entry);
	name = e_contact_sanitise_google_group_name (entry);

	system_group_id = gdata_contacts_group_get_system_group_id (GDATA_CONTACTS_GROUP (entry));
	is_deleted = gdata_contacts_group_is_deleted (GDATA_CONTACTS_GROUP (entry));

	if (system_group_id) {
		g_debug ("Processing %ssystem group %s, %s", is_deleted ? "(deleted) " : "", system_group_id, uid);

		if (is_deleted) {
			gchar *entry_id = g_hash_table_lookup (priv->system_groups_by_id, system_group_id);
			g_hash_table_remove (priv->system_groups_by_entry_id, entry_id);
			g_hash_table_remove (priv->system_groups_by_id, system_group_id);
		} else {
			gchar *entry_id, *system_group_id_dup;

			entry_id = e_contact_sanitise_google_group_id (uid);
			system_group_id_dup = g_strdup (system_group_id);

			g_hash_table_replace (priv->system_groups_by_entry_id, entry_id, system_group_id_dup);
			g_hash_table_replace (priv->system_groups_by_id, system_group_id_dup, entry_id);
		}

		g_free (name);


		name = g_strdup (e_contact_map_google_with_evo_group (system_group_id, TRUE));

		g_warn_if_fail (name != NULL);
		if (!name)
			name = g_strdup (system_group_id);
	}

	if (is_deleted) {
		g_debug ("Processing (deleting) group %s, %s", uid, name);
		g_hash_table_remove (priv->groups_by_id, uid);
		g_hash_table_remove (priv->groups_by_name, name);

		priv->groups_changed = cache_update_group (backend, uid, NULL) || priv->groups_changed;
	} else {
		g_debug ("Processing group %s, %s", uid, name);
		g_hash_table_replace (priv->groups_by_id, e_contact_sanitise_google_group_id (uid), g_strdup (name));
		g_hash_table_replace (priv->groups_by_name, g_strdup (name), e_contact_sanitise_google_group_id (uid));

		priv->groups_changed = cache_update_group (backend, uid, name) || priv->groups_changed;
	}

	g_free (name);
}
