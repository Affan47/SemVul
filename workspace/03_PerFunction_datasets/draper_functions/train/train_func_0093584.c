summary_select_stmt (GHashTable *fields_of_interest,
                     gboolean distinct)
{
	GString *string;

	if (distinct)
		string = g_string_new ("SELECT DISTINCT summary.uid");
	else
		string = g_string_new ("SELECT summary.uid");


	if (g_hash_table_size (fields_of_interest) == 2)
		g_string_append (string, ", Rev");

	return g_string_free (string, FALSE);
}
