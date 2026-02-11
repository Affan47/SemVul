bitset_equal(struct bitset *from, struct bitset *to)
{
	unsigned long *src, *dest;
	unsigned long i, size;

	dest = to->bits;
	src = from->bits;
	size = max(from->size, to->size);

	for (i = 0; i < size / BYTES_PER_LONG; i++) {
		if (dest[i] != src[i])
			return false;
	}
	return true;
}
