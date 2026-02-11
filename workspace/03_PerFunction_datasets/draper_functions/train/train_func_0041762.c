abi_stock_from_menu_id (XAP_Menu_Id menu_id)
{
	gint i;


	i = 0;
	while (stock_mapping[i].abi_stock_id) {
		if (menu_id == stock_mapping[i].menu_id) {
			return stock_mapping[i].gtk_stock_id;
		}
		i++;
	}


	i = 0;
	while (stock_entries[i].abi_stock_id) {
		if (menu_id == stock_entries[i].menu_id) {
			return stock_entries[i].abi_stock_id;
		}
		i++;
	}

	return NULL;
}
