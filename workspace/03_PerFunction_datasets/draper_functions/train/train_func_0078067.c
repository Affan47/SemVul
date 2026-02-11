clear_reference_bitmap (MonoBitSet **sets, guint32 offset, guint32 size)
{
	int idx = ACCESS_SPECIAL_STATIC_OFFSET (offset, index);
	MonoBitSet *rb = sets [idx];
	offset = ACCESS_SPECIAL_STATIC_OFFSET (offset, offset);
	offset /= sizeof (uintptr_t);

	for (int i = 0; i < size / sizeof (uintptr_t); i++)
		mono_bitset_clear_fast (rb, offset + i);
}
