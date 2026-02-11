mono_gc_make_descr_for_array (int vector, gsize *elem_bitmap, int numbits, size_t elem_size)
{
	int first_set = -1, num_set = 0, last_set = -1, i;
	mword desc = DESC_TYPE_VECTOR | (vector ? VECTOR_KIND_SZARRAY : VECTOR_KIND_ARRAY);
	for (i = 0; i < numbits; ++i) {
		if (elem_bitmap [i / GC_BITS_PER_WORD] & ((gsize)1 << (i % GC_BITS_PER_WORD))) {
			if (first_set < 0)
				first_set = i;
			last_set = i;
			num_set++;
		}
	}

	if (first_set < 0) {
		if (elem_size <= MAX_ELEMENT_SIZE)
			return (void*)(desc | VECTOR_SUBTYPE_PTRFREE | (elem_size << VECTOR_ELSIZE_SHIFT));
		return (void*)DESC_TYPE_COMPLEX_PTRFREE;
	}

	if (elem_size <= MAX_ELEMENT_SIZE) {
		desc |= elem_size << VECTOR_ELSIZE_SHIFT;
		if (!num_set) {
			return (void*)(desc | VECTOR_SUBTYPE_PTRFREE);
		}

		if (num_set * sizeof (gpointer) == elem_size) {
			return (void*)(desc | VECTOR_SUBTYPE_REFS | ((gssize)(-1) << 16));
		}


		if (last_set < SMALL_BITMAP_SIZE) {
			return (void*)(desc | VECTOR_SUBTYPE_BITMAP | (*elem_bitmap << 16));
		}
	}

	desc = DESC_TYPE_COMPLEX_ARR;
	desc |= alloc_complex_descriptor (elem_bitmap, last_set + 1) << LOW_TYPE_BITS;
	return (void*) desc;
}
