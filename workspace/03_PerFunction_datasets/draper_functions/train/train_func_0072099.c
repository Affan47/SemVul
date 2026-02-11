lv_move_pv_dup(struct dm_pool *mem, const struct logical_volume *lv)
{
	struct lv_segment *seg;

	dm_list_iterate_items(seg, &lv->segments) {
		if (seg->status & PVMOVE)
			return dm_pool_strdup(mem, dev_name(seg_dev(seg, 0)));
	}
	return NULL;
}
