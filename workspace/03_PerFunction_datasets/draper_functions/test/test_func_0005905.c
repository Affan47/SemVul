merge(pairingheap *heap, pairingheap_node *a, pairingheap_node *b)
{
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;


	if (heap->ph_compare(a, b, heap->ph_arg) < 0)
	{
		pairingheap_node *tmp;

		tmp = a;
		a = b;
		b = tmp;
	}


	if (a->first_child)
		a->first_child->prev_or_parent = b;
	b->prev_or_parent = a;
	b->next_sibling = a->first_child;
	a->first_child = b;

	return a;
}
