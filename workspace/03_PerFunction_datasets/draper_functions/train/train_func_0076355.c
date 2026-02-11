cd_mapping_db_get_timestamp (CdMappingDb *mdb,
			     const gchar *device_id,
			     const gchar *profile_id,
			     GError  **error)
{
	gchar *error_msg = NULL;
	gchar *statement;
	gint rc;
	guint64 timestamp = G_MAXUINT64;

	g_return_val_if_fail (CD_IS_MAPPING_DB (mdb), G_MAXUINT64);
	g_return_val_if_fail (mdb->priv->db != NULL, G_MAXUINT64);

	g_debug ("CdMappingDb: get checksum for %s<->%s",
		 device_id, profile_id);
	statement = sqlite3_mprintf ("SELECT timestamp FROM mappings_v2 WHERE "
				     "device = '%q' AND profile = '%q' "
				     "LIMIT 1;", device_id, profile_id);


	rc = sqlite3_exec (mdb->priv->db,
			   statement,
			   cd_mapping_db_sqlite_timestamp_cb,
			   &timestamp,
			   &error_msg);
	if (rc != SQLITE_OK) {
		g_set_error (error,
			     CD_CLIENT_ERROR,
			     CD_CLIENT_ERROR_INTERNAL,
			     "SQL error: %s",
			     error_msg);
		sqlite3_free (error_msg);
		goto out;
	}


	if (timestamp == G_MAXUINT64) {
		g_set_error (error,
			     CD_CLIENT_ERROR,
			     CD_CLIENT_ERROR_INTERNAL,
			     "device and profile %s<>%s not found",
			     device_id, profile_id);
		goto out;
	}
out:
	sqlite3_free (statement);
	return timestamp;
}
