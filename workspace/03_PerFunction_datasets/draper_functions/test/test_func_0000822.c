mono_bitset_sub (MonoBitSet *dest, const MonoBitSet *src) {
	int i, size;

	g_assert (src->size <= dest->size);

	size = src->size / BITS_PER_CHUNK;
	for (i = 0; i < size; ++i)
		dest->data [i] &= ~src->data [i];
}
