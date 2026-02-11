mono_lock_free_free (gpointer ptr)
{
	Anchor old_anchor, new_anchor;
	Descriptor *desc;
	gpointer sb;
	MonoLockFreeAllocator *heap = NULL;

	desc = DESCRIPTOR_FOR_ADDR (ptr);
	sb = desc->sb;
	g_assert (SB_HEADER_FOR_ADDR (ptr) == SB_HEADER_FOR_ADDR (sb));

	do {
		new_anchor = old_anchor = *(volatile Anchor*)&desc->anchor.value;
		*(unsigned int*)ptr = old_anchor.data.avail;
		new_anchor.data.avail = ((char*)ptr - (char*)sb) / desc->slot_size;
		g_assert (new_anchor.data.avail < SB_USABLE_SIZE / desc->slot_size);

		if (old_anchor.data.state == STATE_FULL)
			new_anchor.data.state = STATE_PARTIAL;

		if (++new_anchor.data.count == desc->max_count) {
			heap = desc->heap;
			new_anchor.data.state = STATE_EMPTY;
		}
	} while (!set_anchor (desc, old_anchor, new_anchor));

	if (new_anchor.data.state == STATE_EMPTY) {
		g_assert (old_anchor.data.state != STATE_EMPTY);

		if (InterlockedCompareExchangePointer ((gpointer * volatile)&heap->active, NULL, desc) == desc) {

			desc_retire (desc);
		} else {


			list_remove_empty_desc (heap->sc);
		}
	} else if (old_anchor.data.state == STATE_FULL) {


		g_assert (new_anchor.data.state == STATE_PARTIAL);

		if (InterlockedCompareExchangePointer ((gpointer * volatile)&desc->heap->active, desc, NULL) != NULL)
			heap_put_partial (desc);
	}
}
