calc_subtree_size(branch_t *b, int *x, int *y, int *w, int *h)
{
	int i, j;

	rect_union(x, y, w, h, b);

	for(i = 0; i < b->nrevs; i++)
	{
		for(j = 0; j < b->revs[i]->nbranches; j++)
			calc_subtree_size(b->revs[i]->branches[j], x, y, w, h);
	}
}
