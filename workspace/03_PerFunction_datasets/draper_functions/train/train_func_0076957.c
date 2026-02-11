vmci_handle_arr_get_handles(struct vmci_handle_arr *array)
{
	if (array->size)
		return array->entries;

	return NULL;
}
