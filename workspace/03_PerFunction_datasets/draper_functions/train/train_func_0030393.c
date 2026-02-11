git_revwalk_list_pop_back(git_revwalk_list *list)
{
	git_revwalk_listnode *node;
	git_revwalk_commit *commit;

	if (list->tail == NULL)
		return NULL;

	node = list->tail;
	list->tail = list->tail->prev;
	if (list->tail == NULL)
		list->head = NULL;

	commit = node->walk_commit;
	free(node);

	list->size--;

	return commit;
}
