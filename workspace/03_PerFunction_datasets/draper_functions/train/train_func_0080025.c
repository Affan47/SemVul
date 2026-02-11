midgard_core_schema_type_add_table (MgdSchemaTypeAttr *type, const gchar *table)
{
	g_assert (type != NULL);
	g_assert (table != NULL);

	if (type->tableshash == NULL)
		return;

	g_hash_table_insert (type->tableshash, g_strdup(table), NULL);

	GString *_sql = g_string_new ("");
	_str_cont *cont = g_new (_str_cont, 1);
	cont->string = _sql;
	cont->elts = 0;

	g_hash_table_foreach (type->tableshash, __build_tables_static_string, cont);
	g_free ((gchar *)type->tables);
	type->tables = g_strdup (_sql->str);
	g_string_free (_sql, TRUE);
	g_free (cont);
}
