gfree(void* ptr)
{
	Slot* slot = slotlist;
	Slot* prev_slot = NULL;
	while(slot+1 != ptr)
	{
		if (slot == NULL)
			return;
		prev_slot = slot;
		slot = slot->next;
	}
	slot->free = 1;
	if (slot->next && slot->next->free)
		merge_slots(slot);
	if (prev_slot && prev_slot->free)
		merge_slots(prev_slot);
#ifdef MEMORY_DEBUG
	printf("freeing 0x%x\n",(int)ptr);
#endif
}
