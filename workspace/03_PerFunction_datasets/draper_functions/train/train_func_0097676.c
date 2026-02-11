array_insert(void *base, size_t elt_size, unsigned nr_elts,
			 unsigned index, void *elt)
	__dm_written_to_disk(elt)
{
	if (index < nr_elts)
		memmove(base + (elt_size * (index + 1)),
			base + (elt_size * index),
			(nr_elts - index) * elt_size);

	memcpy_disk(base + (elt_size * index), elt, elt_size);
}
