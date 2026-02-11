hwloc_bitmap_last(const struct hwloc_bitmap_s * set)
{
	int i;

	HWLOC__BITMAP_CHECK(set);

	if (set->infinite)
		return -1;

	for(i=set->ulongs_count-1; i>=0; i--) {

		unsigned long w = set->ulongs[i];
		if (w)
			return hwloc_flsl(w) - 1 + HWLOC_BITS_PER_LONG*i;
	}

	return -1;
}
