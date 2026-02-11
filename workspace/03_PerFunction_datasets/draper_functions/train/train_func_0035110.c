unsetSymbolManager ()
{
	if (_query_scope)
		g_object_unref (_query_scope);
	_query_scope = NULL;

	if (_query_search)
		g_object_unref (_query_search);
	_query_search = NULL;

	if (_query_search_in_scope)
		g_object_unref (_query_search_in_scope);
	_query_search_in_scope = NULL;

	if (_query_parent_scope)
		g_object_unref (_query_parent_scope);
	_query_parent_scope = NULL;
}
