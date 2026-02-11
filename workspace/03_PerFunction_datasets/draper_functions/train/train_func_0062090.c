bitmap_get_counter(struct bitmap_counts *bitmap,
					    sector_t offset, sector_t *blocks,
					    int create)
__releases(bitmap->lock)
__acquires(bitmap->lock)
{


	sector_t chunk = offset >> bitmap->chunkshift;
	unsigned long page = chunk >> PAGE_COUNTER_SHIFT;
	unsigned long pageoff = (chunk & PAGE_COUNTER_MASK) << COUNTER_BYTE_SHIFT;
	sector_t csize;
	int err;

	err = bitmap_checkpage(bitmap, page, create);

	if (bitmap->bp[page].hijacked ||
	    bitmap->bp[page].map == NULL)
		csize = ((sector_t)1) << (bitmap->chunkshift +
					  PAGE_COUNTER_SHIFT - 1);
	else
		csize = ((sector_t)1) << bitmap->chunkshift;
	*blocks = csize - (offset & (csize - 1));

	if (err < 0)
		return NULL;


	if (bitmap->bp[page].hijacked) {


		int hi = (pageoff > PAGE_COUNTER_MASK);
		return  &((bitmap_counter_t *)
			  &bitmap->bp[page].map)[hi];
	} else
		return (bitmap_counter_t *)
			&(bitmap->bp[page].map[pageoff]);
}
