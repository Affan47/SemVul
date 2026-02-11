_for_each_pv(struct cmd_context *cmd, struct logical_volume *lv,
			uint32_t le, uint32_t len, struct lv_segment *seg,
			uint32_t *max_seg_len,
			uint32_t first_area, uint32_t max_areas,
			int top_level_area_index,
			int only_single_area_segments,
			int (*fn)(struct cmd_context *cmd,
				  struct pv_segment *peg, uint32_t s,
				  void *data),
			void *data)
{
	uint32_t s;
	uint32_t remaining_seg_len, area_len, area_multiple;
	uint32_t stripes_per_mimage = 1;
	int r = 1;

	if (!seg && !(seg = find_seg_by_le(lv, le))) {
		log_error("Failed to find segment for %s extent %" PRIu32,
			  lv->name, le);
		return 0;
	}


	remaining_seg_len = seg->len - (le - seg->le);

	if (remaining_seg_len > len)
		remaining_seg_len = len;

	if (max_seg_len && *max_seg_len > remaining_seg_len)
		*max_seg_len = remaining_seg_len;

	area_multiple = _calc_area_multiple(seg->segtype, seg->area_count, 0);
	area_len = remaining_seg_len / area_multiple ? : 1;


	if (top_level_area_index == -1)
		stripes_per_mimage = _stripes_per_mimage(seg);

	for (s = first_area;
	     s < seg->area_count && (!max_areas || s <= max_areas);
	     s++) {
		if (seg_type(seg, s) == AREA_LV) {
			if (!(r = _for_each_pv(cmd, seg_lv(seg, s),
					       seg_le(seg, s) +
					       (le - seg->le) / area_multiple,
					       area_len, NULL, max_seg_len, 0,
					       (stripes_per_mimage == 1) && only_single_area_segments ? 1U : 0U,
					       (top_level_area_index != -1) ? top_level_area_index : (int) (s * stripes_per_mimage),
					       only_single_area_segments, fn,
					       data)))
				stack;
		} else if (seg_type(seg, s) == AREA_PV)
			if (!(r = fn(cmd, seg_pvseg(seg, s), top_level_area_index != -1 ? (uint32_t) top_level_area_index + s : s, data)))
				stack;
		if (r != 1)
			return r;
	}


	if (!only_single_area_segments && seg_is_mirrored(seg) && seg->log_lv) {
		if (!(r = _for_each_pv(cmd, seg->log_lv, 0, seg->log_lv->le_count, NULL,
				       NULL, 0, 0, 0, only_single_area_segments,
				       fn, data)))
			stack;
		if (r != 1)
			return r;
	}


	return 1;
}
