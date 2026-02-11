mb_buddy_mark_free(struct ext4_buddy *e4b, int first, int last)
{
	int max;
	int order = 1;
	void *buddy = mb_find_buddy(e4b, order, &max);

	while (buddy) {
		void *buddy2;


		if (first & 1)
			e4b->bd_info->bb_counters[order] += mb_buddy_adjust_border(&first, buddy, -1);
		if (!(last & 1))
			e4b->bd_info->bb_counters[order] += mb_buddy_adjust_border(&last, buddy, 1);
		if (first > last)
			break;
		order++;

		if (first == last || !(buddy2 = mb_find_buddy(e4b, order, &max))) {
			mb_clear_bits(buddy, first, last - first + 1);
			e4b->bd_info->bb_counters[order - 1] += last - first + 1;
			break;
		}
		first >>= 1;
		last >>= 1;
		buddy = buddy2;
	}
}
