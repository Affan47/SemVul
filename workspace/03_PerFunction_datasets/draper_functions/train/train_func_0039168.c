wb_over_bg_thresh(struct bdi_writeback *wb)
{
	struct dirty_throttle_control gdtc_stor = { GDTC_INIT(wb) };
	struct dirty_throttle_control mdtc_stor = { MDTC_INIT(wb, &gdtc_stor) };
	struct dirty_throttle_control * const gdtc = &gdtc_stor;
	struct dirty_throttle_control * const mdtc = mdtc_valid(&mdtc_stor) ?
						     &mdtc_stor : NULL;


	gdtc->avail = global_dirtyable_memory();
	gdtc->dirty = global_page_state(NR_FILE_DIRTY) +
		      global_page_state(NR_UNSTABLE_NFS);
	domain_dirty_limits(gdtc);

	if (gdtc->dirty > gdtc->bg_thresh)
		return true;

	if (wb_stat(wb, WB_RECLAIMABLE) >
	    wb_calc_thresh(gdtc->wb, gdtc->bg_thresh))
		return true;

	if (mdtc) {
		unsigned long filepages, headroom, writeback;

		mem_cgroup_wb_stats(wb, &filepages, &headroom, &mdtc->dirty,
				    &writeback);
		mdtc_calc_avail(mdtc, filepages, headroom);
		domain_dirty_limits(mdtc);

		if (mdtc->dirty > mdtc->bg_thresh)
			return true;

		if (wb_stat(wb, WB_RECLAIMABLE) >
		    wb_calc_thresh(mdtc->wb, mdtc->bg_thresh))
			return true;
	}

	return false;
}
