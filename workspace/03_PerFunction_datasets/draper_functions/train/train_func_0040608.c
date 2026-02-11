display_stripe(const struct lv_segment *seg, uint32_t s, const char *pre)
{
	switch (seg_type(seg, s)) {
	case AREA_PV:

		log_print("%sPhysical volume\t%s", pre,
			  seg_pv(seg, s) ?
			  pv_dev_name(seg_pv(seg, s)) :
			    "Missing");

		if (seg_pv(seg, s))
			log_print("%sPhysical extents\t%d to %d", pre,
				  seg_pe(seg, s),
				  seg_pe(seg, s) + seg->area_len - 1);
		break;
	case AREA_LV:
		log_print("%sLogical volume\t%s", pre,
			  seg_lv(seg, s) ?
			  seg_lv(seg, s)->name : "Missing");

		if (seg_lv(seg, s))
			log_print("%sLogical extents\t%d to %d", pre,
				  seg_le(seg, s),
				  seg_le(seg, s) + seg->area_len - 1);
		break;
	case AREA_UNASSIGNED:
		log_print("%sUnassigned area", pre);
	}
}
