dico_list_destroy(struct dico_list **plist)
{
    struct dico_list *list;

    if (!plist || !*plist)
	return;

    list = *plist;
    *plist = NULL;

    dico_list_clear(list);
    free(list);
}
