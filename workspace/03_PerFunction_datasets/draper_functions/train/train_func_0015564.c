sdb_engine_add_new_symbol_case_1 (SymbolDBEngine *dbe,
    							  gint symbol_id,
    							  GdaSet **plist_ptr,
								  GdaStatement **stmt_ptr)
{
	GdaHolder *param;
	GValue v = {0};

	const GdaSet * plist = *plist_ptr;
	const GdaStatement * stmt = *stmt_ptr;


	if ((stmt = sdb_engine_get_statement_by_query_id (dbe,
											 PREP_QUERY_UPDATE_SYMBOL_ALL))
		== NULL)
	{
		g_warning ("query is null");
		return;
	}

	plist = sdb_engine_get_query_parameters_list (dbe, PREP_QUERY_UPDATE_SYMBOL_ALL);


	if ((param = gda_set_get_holder ((GdaSet*)plist, "symbolid")) == NULL)
	{
		g_warning ("param isfilescope is NULL from pquery!");
		return;
	}

	SDB_PARAM_SET_INT(param, symbol_id);

	*plist_ptr = (GdaSet*)plist;
	*stmt_ptr = (GdaStatement*)stmt;
}
