get_real_table_field (MidgardQueryExecutor *executor, MidgardSqlQueryColumn *column)
{
	g_return_val_if_fail (executor != NULL, NULL);
	g_return_val_if_fail (column != NULL, NULL);

	MidgardConnection *mgd = executor->priv->mgd;
	g_return_val_if_fail (executor != NULL, NULL);


	MidgardDBObjectClass *dbklass = NULL;
	if (executor->priv->storage)
		dbklass = executor->priv->storage->priv->klass;

       	gchar *classname = NULL;
	gchar *pname = NULL;
	MidgardQueryStorage *storage = NULL;


	MidgardQueryProperty *qproperty = midgard_query_column_get_query_property (MIDGARD_QUERY_COLUMN(column), NULL);
	g_object_get (qproperty, "storage", &storage, "property", &pname, NULL);
	if (storage)
		g_object_get (storage, "dbclass", &classname, NULL);
	g_object_unref (qproperty);
	if (classname) {
		GType dbtype = g_type_from_name (classname);

		dbklass = MIDGARD_DBOBJECT_CLASS (g_type_class_peek (dbtype));
	}


	const gchar *fieldname = (const gchar *)pname;
	if (dbklass)
		fieldname = midgard_core_class_get_property_colname (dbklass, pname);

	const gchar *qualifier = midgard_query_column_get_qualifier (MIDGARD_QUERY_COLUMN (column), NULL);
	if (*qualifier == '\0')
		qualifier = NULL;

	gchar *table_alias_field = g_strdup_printf("%s%s%s",
			qualifier ? qualifier : "",
			qualifier ? "." : "",
			fieldname);

	g_free (classname);
	g_free (pname);

	return table_alias_field;
}
