hwloc_bitmap_next(const struct hwloc_bitmap_s * set, int prev_cpu)
{
	unsigned i = HWLOC_SUBBITMAP_INDEX(prev_cpu + 1);

	HWLOC__BITMAP_CHECK(set);

	if (i >= set->ulongs_count) {
		if (set->infinite)
			return prev_cpu + 1;
		else
			return -1;
	}

	for(; i<set->ulongs_count; i++) {

		unsigned long w = set->ulongs[i];


		if (prev_cpu >= 0 && HWLOC_SUBBITMAP_INDEX((unsigned) prev_cpu) == i)
			w &= ~HWLOC_SUBBITMAP_ULBIT_TO(HWLOC_SUBBITMAP_CPU_ULBIT(prev_cpu));

		if (w)
			return hwloc_ffsl(w) - 1 + HWLOC_BITS_PER_LONG*i;
	}

	if (set->infinite)
		return set->ulongs_count * HWLOC_BITS_PER_LONG;

	return -1;
}
