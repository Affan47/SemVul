_form_mirror(struct cmd_context *cmd, struct alloc_handle *ah,
			struct logical_volume *lv,
			uint32_t mirrors, uint32_t stripes,
			uint32_t stripe_size, uint32_t region_size, int log)
{
	struct logical_volume **img_lvs;


	if (dm_list_size(&lv->segments) != 1 ||
	    seg_type(first_seg(lv), 0) != AREA_LV)
		if (!insert_layer_for_lv(cmd, lv, 0, "_mimage_%d"))
			return 0;


	if (!(img_lvs = alloca(sizeof(*img_lvs) * mirrors))) {
		log_error("img_lvs allocation failed. "
			  "Remove new LV and retry.");
		return 0;
	}

	if (!_create_mimage_lvs(ah, mirrors, stripes, stripe_size, lv, img_lvs, log))
		return 0;

	if (!lv_add_mirror_lvs(lv, img_lvs, mirrors,
			       MIRROR_IMAGE | (lv->status & LOCKED),
			       region_size)) {
		log_error("Aborting. Failed to add mirror segment. "
			  "Remove new LV and retry.");
		return 0;
	}

	return 1;
}
