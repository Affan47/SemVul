free_int(void* p, heap_t* heap) {
	if(!p) return;
	header_t* head = (header_t*)((u32int)p-sizeof(header_t));
	if(head->magic != MAGIC_USED) return;
	head->magic=MAGIC_FREE;

	header_t* next = (header_t*)((u32int)head + sizeof(header_t) + sizeof(footer_t) + head->size);
	if(next->magic==MAGIC_FREE) {
		if(next->size == ALL_MEM) {
			head->size = ALL_MEM;
		} else {
			head->size = head->size + next->size + sizeof(header_t) + sizeof(footer_t);
			footer_t* foot = (footer_t*)((u32int)head + sizeof(header_t) + head->size);
			foot->head = head;
		}
	}

	if(heap->start_addr != (u32int)head) {
		header_t* prev = ((footer_t*)((u32int)head-sizeof(footer_t)))->head;
		if(prev->magic == MAGIC_FREE) {
			if(head->size == ALL_MEM) {
				prev->size = ALL_MEM;
			} else {
				prev->size = prev->size + head->size + sizeof(header_t) + sizeof(footer_t);
				footer_t* foot = (footer_t*)((u32int)prev + sizeof(header_t) + prev->size);
				foot->head = prev;
			}
		}
	}
}
