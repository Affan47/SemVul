catalog_get_function (GladeCatalog *catalog,
		      const gchar *symbol_name,
		      gpointer *symbol_ptr)
{
	if (catalog->module == NULL)
		catalog->module = glade_util_load_library (catalog->library);

	if (catalog->module)
		return g_module_symbol (catalog->module, symbol_name, symbol_ptr);

	return FALSE;
}
