llistRemoveCurrentAndGetNext (LList *list, void **iterator)
{
	LNode *prevNode, *node;


	if (list == NULL || iterator == NULL || *iterator == NULL)
		return NULL;


	prevNode = *(LNode **)iterator;
	node = prevNode->next;
	if (node)
	{
		prevNode->next = node->next;
		if (list->tail == node) {
			list->tail = prevNode;
		}
		_llistDestroyNode (&node, NULL);
		node = prevNode->next;
		if (node) {
			return node->data;
		} else {
			return NULL;
		}
	}
	else
		return NULL;
}
