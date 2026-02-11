nssList_GetArray(nssList *list, void **rvArray, PRUint32 maxElements)
{
    nssListElement *node;
    PRUint32 i = 0;
    PR_ASSERT(maxElements > 0);
    node = list->head;
    if (!node) {
	return PR_SUCCESS;
    }
    NSSLIST_LOCK_IF(list);
    while (node) {
	rvArray[i++] = node->data;
	if (i == maxElements) break;
	node = (nssListElement *)PR_NEXT_LINK(&node->link);
	if (node == list->head) {
	    break;
	}
    }
    NSSLIST_UNLOCK_IF(list);
    return PR_SUCCESS;
}
