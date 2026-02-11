ldapu_list_free (LDAPUList_t *list, LDAPUListNodeFn_t free_fn)
{
    if (list) {
	auto LDAPUListNode_t *node = list->head;
	while (node) {
	    auto LDAPUListNode_t *next = node->next;
	    if (free_fn) {
		(*free_fn)(node->info, 0);
		node->info = 0;
	    }
	    node->info = 0;
	    free(node);
	    node = next;
	}
	list->head = 0;
	list->tail = 0;
    }
    return;
}
