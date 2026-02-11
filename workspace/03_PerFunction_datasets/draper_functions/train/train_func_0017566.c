wlcore_fw_status(struct wl1271 *wl, struct wl_fw_status *status)
{
	struct wl12xx_vif *wlvif;
	struct timespec ts;
	u32 old_tx_blk_count = wl->tx_blocks_available;
	int avail, freed_blocks;
	int i;
	int ret;
	struct wl1271_link *lnk;

	ret = wlcore_raw_read_data(wl, REG_RAW_FW_STATUS_ADDR,
				   wl->raw_fw_status,
				   wl->fw_status_len, false);
	if (ret < 0)
		return ret;

	wlcore_hw_convert_fw_status(wl, wl->raw_fw_status, wl->fw_status);

	wl1271_debug(DEBUG_IRQ, "intr: 0x%x (fw_rx_counter = %d, "
		     "drv_rx_counter = %d, tx_results_counter = %d)",
		     status->intr,
		     status->fw_rx_counter,
		     status->drv_rx_counter,
		     status->tx_results_counter);

	for (i = 0; i < NUM_TX_QUEUES; i++) {

		wl->tx_allocated_pkts[i] -=
				(status->counters.tx_released_pkts[i] -
				wl->tx_pkts_freed[i]) & 0xff;

		wl->tx_pkts_freed[i] = status->counters.tx_released_pkts[i];
	}


	for_each_set_bit(i, wl->links_map, wl->num_links) {
		u8 diff;
		lnk = &wl->links[i];


		diff = (status->counters.tx_lnk_free_pkts[i] -
		       lnk->prev_freed_pkts) & 0xff;

		if (diff == 0)
			continue;

		lnk->allocated_pkts -= diff;
		lnk->prev_freed_pkts = status->counters.tx_lnk_free_pkts[i];


		lnk->total_freed_pkts += diff;
	}


	if (likely(wl->tx_blocks_freed <= status->total_released_blks))
		freed_blocks = status->total_released_blks -
			       wl->tx_blocks_freed;
	else
		freed_blocks = 0x100000000LL - wl->tx_blocks_freed +
			       status->total_released_blks;

	wl->tx_blocks_freed = status->total_released_blks;

	wl->tx_allocated_blocks -= freed_blocks;


	if (freed_blocks) {
		if (wl->tx_allocated_blocks)
			wl12xx_rearm_tx_watchdog_locked(wl);
		else
			cancel_delayed_work(&wl->tx_watchdog_work);
	}

	avail = status->tx_total - wl->tx_allocated_blocks;


	wl->tx_blocks_available = max((int)wl->tx_blocks_available,
				      avail);


	if (wl->tx_blocks_available > old_tx_blk_count)
		clear_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags);


	wl12xx_for_each_wlvif_ap(wl, wlvif) {
		wl12xx_irq_update_links_status(wl, wlvif, status);
	}


	getnstimeofday(&ts);
	wl->time_offset = (timespec_to_ns(&ts) >> 10) -
		(s64)(status->fw_localtime);

	wl->fw_fast_lnk_map = status->link_fast_bitmap;

	return 0;
}
