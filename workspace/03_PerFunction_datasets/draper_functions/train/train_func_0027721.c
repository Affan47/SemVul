menu_delqueue(dialogparam ** d)
{
    const struct menuitem *item;
    struct queuelist *list = firstqueue;
    if (firstqueue == NULL)
	return NULL;
    item = firstqueue->item;
    *d = firstqueue->d;
    firstqueue = list->next;
    if (list->next != NULL)
	list->next->previous = NULL;
    else
	lastqueue = NULL;
    free(list);
    return (item);
}
