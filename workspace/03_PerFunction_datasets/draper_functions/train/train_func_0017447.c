construct_deep_array(int f[], int N, int deep[])
{
	int n = N;
	static struct heap_node *heap[500];
	int i;
	int total = 0;

	for (i = 0 ; i < n ; i++)
		deep[i] = 0;

	for (i = 0 ; i < n ; i++)
	{
		if (f[i] > 0)
		{
			struct heap_node *p = (struct heap_node *)malloc(sizeof(struct heap_node));
			struct leaf_node *q = (struct leaf_node *)malloc(sizeof(struct leaf_node));

			q->pos = i;
			q->next = 0;

			p->val = f[i];
			p->list = q;
			p->last_ref = &q->next;

			heap[++total] = p;

		}
	}

	n = total;

	for (i = n / 2 ; i > 0 ; i--)
		top_to_down(heap, n, i);

	while (n > 1)
	{
		struct heap_node *a, *b;
		struct leaf_node *p;

		a = heap[1];

		heap[1] = heap[n];
		n--;
		top_to_down(heap, n, 1);
		b = heap[1];

		a->val += b->val;


		for (p = a->list ; p != 0 ; p = p->next)
			deep[p->pos]++;

		for (p = b->list ; p != 0 ; p = p->next)
			deep[p->pos]++;

		*a->last_ref = b->list;
		a->last_ref = b->last_ref;

		free(b);
		heap[1] = a;
		top_to_down(heap, n, 1);
	}

	{
		struct leaf_node *p;

		for (p = heap[1]->list ; p != 0 ;)
		{
			struct leaf_node *next = p->next;
			free(p);
			p = next;
		}
	}

	return total;
}
