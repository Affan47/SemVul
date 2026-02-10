catalog_list_load_current_child (CatalogListData *list_data)
{
	if (list_data->current_child == NULL) {
		catalog_list_load_next_child (list_data->parent);
		catalog_list_data_free (list_data);
		return;
	}

	load_catalog_list ((CatalogListData *) list_data->current_child->data);
}
