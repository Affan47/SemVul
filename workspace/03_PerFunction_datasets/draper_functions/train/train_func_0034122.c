on_line_parse_output (const gchar *line, gpointer user_data)
{
	GcrGnupgCollectionLoad *load = user_data;
	GcrRecord *record;
	GQuark schema;

	_gcr_debug ("output: %s", line);

	record = _gcr_record_parse_colons (line, -1);
	if (!record) {
		g_warning ("invalid gnupg output line: %s", line);
		return;
	}

	schema = _gcr_record_get_schema (record);


	if (schema == GCR_RECORD_SCHEMA_PUB || schema == GCR_RECORD_SCHEMA_SEC) {
		_gcr_debug ("start of new key");
		if (load->records->len)
			process_records_as_key (load);
		g_assert (!load->records->len);
		g_ptr_array_add (load->records, record);
		record = NULL;


	} else if (schema == GCR_RECORD_SCHEMA_UID ||
	           schema == GCR_RECORD_SCHEMA_FPR) {
		if (load->records->len) {
			g_ptr_array_add (load->records, record);
			record = NULL;
		}
	}

	if (record != NULL)
		_gcr_record_free (record);
}
