_add_log(struct dm_pool *mem, struct lv_segment *seg,
		    const struct lv_activate_opts *laopts,
		    struct dm_tree_node *node, uint32_t area_count, uint32_t region_size)
{
	unsigned clustered = 0;
	char *log_dlid = NULL;
	uint32_t log_flags = 0;


	if (!laopts->exclusive && vg_is_clustered(seg->lv->vg))
		clustered = 1;

	if (seg->log_lv) {

		if (!(log_dlid = build_dm_uuid(mem, seg->log_lv->lvid.s, NULL))) {
			log_error("Failed to build uuid for log LV %s.",
				  seg->log_lv->name);
			return 0;
		}
	} else {

		if (!(log_dlid = build_dm_uuid(mem, seg->lv->lvid.s, NULL))) {
			log_error("Failed to build uuid for mirror LV %s.",
				  seg->lv->name);
			return 0;
		}
		log_flags |= DM_CORELOG;
	}

	if (mirror_in_sync() && !(seg->status & PVMOVE))
		log_flags |= DM_NOSYNC;

	if (_block_on_error_available && !(seg->status & PVMOVE))
		log_flags |= DM_BLOCK_ON_ERROR;

	return dm_tree_node_add_mirror_target_log(node, region_size, clustered, log_dlid, area_count, log_flags);
}
