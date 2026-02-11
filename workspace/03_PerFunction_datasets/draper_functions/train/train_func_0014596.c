sgen_can_alloc_size (size_t size)
{
	SgenFragment *frag;

	if (!SGEN_CAN_ALIGN_UP (size))
		return FALSE;

	size = SGEN_ALIGN_UP (size);

	for (frag = (SgenFragment *)unmask (mutator_allocator.alloc_head); frag; frag = (SgenFragment *)unmask (frag->next)) {
		if ((size_t)(frag->fragment_end - frag->fragment_next) >= size)
			return TRUE;
	}
	return FALSE;
}
