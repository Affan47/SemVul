wl1271_acx_statistics(struct wl1271 *wl, void *stats)
{
	int ret;

	wl1271_debug(DEBUG_ACX, "acx statistics");

	ret = wl1271_cmd_interrogate(wl, ACX_STATISTICS, stats,
				     sizeof(struct acx_header),
				     wl->stats.fw_stats_len);
	if (ret < 0) {
		wl1271_warning("acx statistics failed: %d", ret);
		return -ENOMEM;
	}

	return 0;
}
