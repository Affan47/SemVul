in_fn_table(const char *name)
{
	struct string_list_item *item;

	if (name == NULL)
		return NULL;

	item = string_list_lookup(name, &fn_table);
	if (item != NULL)
		return (struct patch *)item->util;

	return NULL;
}
