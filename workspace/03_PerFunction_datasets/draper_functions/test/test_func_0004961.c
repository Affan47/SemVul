isns_object_find_descendant(isns_object_t *obj, const isns_attr_list_t *keys)
{
	isns_object_list_t list = ISNS_OBJECT_LIST_INIT;
	isns_object_t	*found;

	if (!isns_object_find_descendants(obj, NULL, keys, &list))
		return NULL;

	found = isns_object_get(list.iol_data[0]);
	isns_object_list_destroy(&list);

	return found;
}
