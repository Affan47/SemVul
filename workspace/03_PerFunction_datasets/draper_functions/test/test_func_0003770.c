list_free(list_t *list)
{
	if (list)
		list_free_(list, list->free_data_fn);
}
