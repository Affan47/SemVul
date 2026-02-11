stmemFree(mem_hdr * mem)
{
    mem_node *p;
    while ((p = mem->head)) {
	mem->head = p->next;
	store_mem_size -= SM_PAGE_SIZE;
	stmemNodeFree(p);
    }
    mem->head = mem->tail = NULL;
    mem->origin_offset = 0;
}
