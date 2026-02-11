tracker_db_journal_reader_get_resource (gint         *id,
                                        const gchar **uri)
{
	g_return_val_if_fail (reader.file != NULL || reader.stream != NULL, FALSE);
	g_return_val_if_fail (reader.type == TRACKER_DB_JOURNAL_RESOURCE, FALSE);

	*id = reader.s_id;
	*uri = reader.uri;

	return TRUE;
}
