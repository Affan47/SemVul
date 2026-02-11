getNearestClassInCurrentScopeChainByFileLine (const char* full_file_path,
                                                            unsigned long linenum,
                                                            string &out_type_name)
{
	IAnjutaIterable *iter;


	iter = ianjuta_symbol_query_search_scope (_query_scope, full_file_path,
	                                          linenum, NULL);
	if (iter == NULL)
		return;


	if (iter != NULL)
	{
		do
		{
			IAnjutaIterable *parent_iter;
			IAnjutaSymbol *node = IANJUTA_SYMBOL (iter);
			DEBUG_PRINT ("sym_name = %s", ianjuta_symbol_get_string (node, IANJUTA_SYMBOL_FIELD_NAME, NULL));
			if (ianjuta_symbol_get_sym_type (node, NULL) == IANJUTA_SYMBOL_TYPE_CLASS)
			{
				out_type_name = ianjuta_symbol_get_string (node, IANJUTA_SYMBOL_FIELD_NAME, NULL);
				break;
			}
			parent_iter =
				ianjuta_symbol_query_search_parent_scope (_query_parent_scope,
				                                          node, NULL);

			if (parent_iter &&
			    ianjuta_symbol_get_int (IANJUTA_SYMBOL (iter), IANJUTA_SYMBOL_FIELD_ID, NULL) ==
			    ianjuta_symbol_get_int (IANJUTA_SYMBOL (parent_iter), IANJUTA_SYMBOL_FIELD_ID, NULL))
			{
				g_object_unref (parent_iter);
				break;
			}

			g_object_unref (iter);
			iter = parent_iter;
		} while (iter);
		if (iter)
			g_object_unref (iter);
	}
}
