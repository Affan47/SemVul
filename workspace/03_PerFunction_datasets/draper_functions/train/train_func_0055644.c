branch_set(const tree *tptr, branch *b, const uuid *k, unsigned long long v)
{
	if (b->leaf)
	{
		int idx = binary_search(b->n, k, 0, b->nodes-1);
		if (idx < 0) return 0;
		b->n[idx].v = v;
		return 1;
	}

	branch *last = 0;
	node *n = b->n;
	int i;

	for (i = 0; i < b->nodes; i++, n++)
	{
		int x = uuid_compare(k, &n->k);

		if (x < 0)
			break;

		last = n->b;

		if (x == 0)
			break;
	}

	if (!last)
		return 0;

	return branch_set(tptr, last, k, v);
}
