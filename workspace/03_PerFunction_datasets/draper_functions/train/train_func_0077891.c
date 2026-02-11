__initialize_statement_insert_query_string (MidgardDBObjectClass *klass, gboolean add_workspace)
{
	GString *sql = g_string_new ("INSERT INTO ");
	guint n_props;
	guint i;
	const gchar *table = MGD_DBCLASS_TABLENAME (klass);
	g_return_val_if_fail (table != NULL, NULL);

	g_string_append (sql, table);

	GParamSpec **pspecs = midgard_core_dbobject_class_list_properties (klass, &n_props);
	g_return_val_if_fail (pspecs != NULL, NULL);

	GString *colnames = g_string_new ("");
	GString *values = g_string_new ("");
	const gchar *pk = MGD_DBCLASS_PRIMARY (klass);
	gboolean add_coma = FALSE;

	for (i = 0; i < n_props; i++) {

		if (pk && g_str_equal (pspecs[i]->name, pk))
			continue;

		const gchar *col_name = midgard_core_class_get_property_colname (klass, pspecs[i]->name);
		if (add_coma) {
			g_string_append (colnames, ", ");
			g_string_append (values, ", ");
		}

		g_string_append (colnames, col_name);

		const gchar *type_name = g_type_name (pspecs[i]->value_type);
		if (pspecs[i]->value_type == MIDGARD_TYPE_TIMESTAMP)
			type_name = "string";
		g_string_append_printf (values, "##%s::%s", col_name, type_name);

		add_coma = TRUE;
	}


	if (add_workspace) {
		g_string_append_printf (colnames, ", %s, %s", MGD_WORKSPACE_OID_FIELD, MGD_WORKSPACE_ID_FIELD);
		g_string_append_printf (values, ", ##%s::guint", MGD_WORKSPACE_OID_FIELD);
		g_string_append_printf (values, ", ##%s::guint", MGD_WORKSPACE_ID_FIELD);
	}

	__statement_insert_add_metadata_fields (klass, colnames, values);

	g_string_append_printf (sql, " (%s) VALUES (%s)", colnames->str, values->str);

	g_string_free (colnames, TRUE);
	g_string_free (values, TRUE);

	return g_string_free (sql, FALSE);
}
