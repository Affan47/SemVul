list_delete_all (List l, ListFindF f, void *key)
{
	ListNode *pp;
	void *v;
	int n = 0;

	assert(l != NULL);
	assert(f != NULL);
	list_mutex_lock(&l->mutex);
	assert(l->magic == LIST_MAGIC);

	pp = &l->head;
	while (*pp) {
		if (f((*pp)->data, key)) {
			if ((v = list_node_destroy(l, pp))) {
				if (l->fDel)
					l->fDel(v);
				n++;
			}
		}
		else {
			pp = &(*pp)->next;
		}
	}
	list_mutex_unlock(&l->mutex);

	return n;
}
