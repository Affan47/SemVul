hwloc_bitmap_clr(struct hwloc_bitmap_s * set, unsigned cpu)
{
	unsigned index_ = HWLOC_SUBBITMAP_INDEX(cpu);

	HWLOC__BITMAP_CHECK(set);


	if (!set->infinite && cpu >= set->ulongs_count * HWLOC_BITS_PER_LONG)
		return;

	hwloc_bitmap_realloc_by_cpu_index(set, cpu);
	set->ulongs[index_] &= ~HWLOC_SUBBITMAP_CPU(cpu);
}
