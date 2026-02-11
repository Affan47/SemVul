ebitmap_destroy(struct ebitmap *e)
{
	struct ebitmap_node *n, *temp;

	if (!e)
		return;

	n = e->node;
	while (n) {
		temp = n;
		n = n->next;
		kfree(temp);
	}

	e->highbit = 0;
	e->node = NULL;
	return;
}
