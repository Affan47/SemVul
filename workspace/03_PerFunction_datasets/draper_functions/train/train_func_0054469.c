node_mergesort (Node *head, int size, int (*cmp) (Node *a, Node *b))
{

	if (size == 1) {
		return head;
	} else {
		Node *top = head, *bottom = head;
		int topsize = size / 2, bottomsize = topsize + (size % 2);
		int j = topsize;

		while (j--)
			bottom = node_down (bottom);

		node_up (bottom)->down = NULL;
		bottom->up = NULL;

		top = node_mergesort (top, topsize, cmp);
		bottom = node_mergesort (bottom, bottomsize, cmp);

		return merge (top, bottom, cmp);
	}
}
