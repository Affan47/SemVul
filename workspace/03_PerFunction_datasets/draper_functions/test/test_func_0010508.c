free_heap_table(Heap_table *heap_head)
{
    Heap_table *heap_next;
    Heap_table *heap_tbl;

    for (heap_tbl = heap_head; heap_tbl != NULL; heap_tbl = heap_next) {
        heap_next = heap_tbl->next;
        free_op_entry_list(heap_tbl->members);
        free_op_entry_list(heap_tbl->structure);
        free(heap_tbl);
    }
}
