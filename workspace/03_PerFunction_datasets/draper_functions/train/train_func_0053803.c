binaryheap_build(binaryheap *heap)
{
	int			i;

	for (i = parent_offset(heap->bh_size - 1); i >= 0; i--)
		sift_down(heap, i);
	heap->bh_has_heap_property = true;
}
