_heap_free (Heap * heap)
{
    _heap_foreach (heap, (HeapForEachFunc)heap->data_destroy_func, NULL);
    if (heap->free_array) free (heap->array);
    free (heap);
}
