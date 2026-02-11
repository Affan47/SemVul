bt_heap_init(struct ptr_heap *heap, size_t alloc_len,
	      int gt(void *a, void *b))
{
	heap->ptrs = NULL;
	heap->len = 0;
	heap->alloc_len = 0;
	heap->gt = gt;


	return heap_grow(heap, max_t(size_t, 1, alloc_len));
}
