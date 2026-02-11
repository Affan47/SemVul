realignNodelist(nodelist_t * list, nodelistitem_t * np)
{
    nodelistitem_t *temp;
    nodelistitem_t *prev;

    if (np == list->first)
	return;

    temp = list->first;
    prev = np->prev;

    list->first = np;
    np->prev = NULL;
    list->last->next = temp;
    temp->prev = list->last;
    list->last = prev;
    prev->next = NULL;
}
