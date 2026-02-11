append_item(PAD * pad, const char *name, const char *value, int replace)
{
    ITEM *item;
    LIST *cur, *prev;
    LIST *list;

    if (pad == NULL)
	return 0;


    list = (LIST *) G_malloc((size_t) sizeof(LIST));
    if (list == NULL)
	return 0;
    list->next = NULL;
    list->value = G_store(value);
    if (list->value == NULL) {
	G_free(list);
	return 0;
    }

    item = find_item(pad, name);
    if (item == NULL)
	item = new_item(pad, name);
    if (item == NULL)
	return 0;


    if (replace)
	remove_value(item, value);


    prev = NULL;
    for (cur = item->list; cur != NULL; cur = cur->next)
	prev = cur;

    if (prev == NULL)
	item->list = list;
    else
	prev->next = list;

    return 1;
}
