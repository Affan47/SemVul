free_melement(list l, void (*free_func) (void *))
{
	element e;
	element next;

	for (e = LIST_HEAD(l); e; e = next) {
		next = e->next;
		if (free_func)
			(*free_func) (e->data);
		FREE(e);
	}
}
