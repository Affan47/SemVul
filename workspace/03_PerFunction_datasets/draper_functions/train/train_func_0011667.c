branch_del(tree *tptr, branch *b, const uuid *k)
{
	if (b->leaf)
	{
		int idx = binary_search(b->n, k, 0, b->nodes-1);
		if (idx < 0) return 0;

		while (idx < b->nodes)
		{
			b->n[idx] = b->n[idx+1];
			idx++;
		}

		b->nodes--;
		tptr->leafs--;


		return 1;
	}

	node *last = 0;
	node *n = b->n;
	int i;

	for (i = 0; i < b->nodes; i++, n++)
	{
		int x = uuid_compare(k, &n->k);

		if (x < 0)
			break;

		last = n;

		if (x == 0)
			break;
	}

	if (!last)
		return 0;

	int del = branch_del(tptr, last->b, k);

	if (!last->b->nodes)
	{
		if (!is_active(tptr, last->b))
		{
			free(last->b);
			tptr->branches--;
		}

		while (i < b->nodes)
		{
			last[0] = last[1];
			last++;
			i++;
		}

		b->nodes--;
	}

	return del;
}
