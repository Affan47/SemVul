lv_mirror_count(const struct logical_volume *lv)
{
	struct lv_segment *seg;
	uint32_t s, mirrors;

	if (!(lv->status & MIRRORED))
		return 1;

	seg = first_seg(lv);


	if (!strcmp(seg->segtype->name, "raid10"))
		return 2;

	if (lv->status & PVMOVE)
		return seg->area_count;

	mirrors = 0;

	for (s = 0; s < seg->area_count; s++) {
		if (seg_type(seg, s) != AREA_LV)
			continue;
		if (is_temporary_mirror_layer(seg_lv(seg, s)))
			mirrors += lv_mirror_count(seg_lv(seg, s));
		else
			mirrors++;
	}

	return mirrors ? mirrors : 1;
}
