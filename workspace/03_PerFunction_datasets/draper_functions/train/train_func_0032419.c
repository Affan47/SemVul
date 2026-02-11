freeNodelist(nodelist_t * list)
{
    nodelistitem_t *temp;
    nodelistitem_t *next;

    if (!list)
	return;

    for (temp = list->first; temp; temp = next) {
	next = temp->next;
	free(temp);
    }
    free(list);
}
