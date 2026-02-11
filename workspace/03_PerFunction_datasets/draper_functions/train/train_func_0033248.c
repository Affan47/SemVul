private_item_get_int(private_data_t **data, const char *item_name) {
	private_data_t *item;

	if ((item = private_item_find(data, item_name)))
		return atoi(item->value);

	return 0;
}
