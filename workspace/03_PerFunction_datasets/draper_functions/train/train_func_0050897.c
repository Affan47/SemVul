dico_list_pop(struct dico_list *list)
{
    void *p;
    if (!list->tail)
	return NULL;
    _dico_list_remove_item(list, list->tail, &p);
    return p;
}
