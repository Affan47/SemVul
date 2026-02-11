midgard_core_schema_type_property_set_tablefield (MgdSchemaPropertyAttr *prop, const gchar *table, const gchar *field)
{
	g_assert (prop != NULL);
	g_assert (table != NULL);
	g_assert (field != NULL);


	if (prop->tablefield != NULL)
		g_free ((gchar *)prop->tablefield);

	gchar *_table = g_strdup (table);
	gchar *_field = g_ascii_strdown (field, -1);

	if (prop->table) g_free ( (gchar *)prop->table);
	prop->table = g_strdup(_table);


	midgard_core_schema_type_property_set_table(prop, _table);


	if (prop->field) g_free ( (gchar *)prop->field);
	prop->field = g_strdup(_field);

	prop->tablefield = g_strjoin(".", _table, _field, NULL);

	g_free (_table);
	g_free (_field);
}
