free_skiplist(skiplist *sl)
{
	node *nd, *next;

	nd = sl->head->forward[0];
	free_node(sl->head);

	while (nd) {
		next = nd->forward[0];
		free_node(nd);
		nd = next;
	}

	free(sl);
}
