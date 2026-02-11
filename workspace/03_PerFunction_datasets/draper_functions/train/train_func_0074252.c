plugin_db_catalog_remove_db_category ( GWDBContext *context, GWDBCategoryPK ref) {
	_data *data = NULL;
	GWDBCategory *category = ref;
	GList *categories = NULL;
	gint size = 0, i = 0, index = 0;


	if ( context != NULL && category != NULL) {
		data = gw_db_context_get_data ( context);
		categories = data->categories;
		size = g_list_length ( g_list_first ( categories)) - 1;
		index = gw_db_category_get_index ( category);

		categories = g_list_remove ( categories, gw_db_category_get_ref ( category));
		categories = g_list_first ( categories);
		categories = g_list_first ( categories);

		categories = g_list_nth ( categories, index);

		for ( i = index; i < size; i++) {
			gw_db_category_set_index ( categories->data, gw_db_category_get_index ( categories->data) - 1);
			categories = g_list_next ( categories);
		}

		gw_db_catalog_set_ismodified ( data->catalog, TRUE);

		return 0;
	}

	return -1;
}
