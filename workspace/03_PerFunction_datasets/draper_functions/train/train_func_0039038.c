midgard_schema_read_file(
		MidgardSchema *self, const gchar *filename)
{
	MidgardSchema *schema = self;

	g_assert(schema != NULL);
        g_assert(filename != NULL);

        GHashTable *files = read_schema_files(filename);
        g_hash_table_foreach(files, parse_schema, schema);
        g_hash_table_destroy(files);


        g_hash_table_foreach(schema->types, __get_tdata_foreach, schema);


        g_hash_table_foreach(schema->types, __postconfig_schema_foreach, schema);
}
