_gcr_record_new (GQuark schema,
                 guint n_columns,
                 gchar delimiter)
{
	GcrRecord *result;
	guint i;

	result = g_slice_new0 (GcrRecord);
	result->block = NULL;
	result->delimiter = delimiter;

	for (i = 0; i < n_columns; i++)
		result->columns[i] = "";
	result->columns[0] = g_quark_to_string (schema);
	result->n_columns = n_columns;

	return result;
}
