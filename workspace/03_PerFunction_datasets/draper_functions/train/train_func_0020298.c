__add_workspace_columns (MidgardConnection *mgd, MidgardDBObjectClass *klass)
{

	const gchar *table = MGD_DBCLASS_TABLENAME (klass);
	MidgardDBColumn *mdc = midgard_core_dbcolumn_new ();
	mdc->table_name = table;
	mdc->column_name = MGD_WORKSPACE_ID_FIELD;
	mdc->index = TRUE;
	mdc->dbtype = "int";
	mdc->gtype = MGD_TYPE_INT;
	mdc->unique = FALSE;
	mdc->dvalue = "0";

	gboolean rv = midgard_core_query_add_column (mgd, mdc);
	g_free (mdc);
	if (!rv)
		return FALSE;


	mdc = midgard_core_dbcolumn_new ();
	mdc->table_name = table;
	mdc->column_name = MGD_WORKSPACE_OID_FIELD;
	mdc->index = TRUE;
	mdc->dbtype = "int";
	mdc->gtype = MGD_TYPE_INT;
	mdc->unique = FALSE;
	mdc->dvalue = "0";

	rv = midgard_core_query_add_column (mgd, mdc);
	g_free (mdc);
	if (!rv)
		return FALSE;

	return TRUE;
}
