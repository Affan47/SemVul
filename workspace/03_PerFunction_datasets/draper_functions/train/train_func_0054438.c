_wi_array_add_data(wi_array_t *array, void *data) {
	_wi_array_item_t	*item;

	item = _wi_array_create_item(array);
	item->data = _WI_ARRAY_RETAIN(array, data);

	_wi_array_add_item(array, item);
}
