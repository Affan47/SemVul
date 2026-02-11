wl1271_rx_filter_enable(struct wl1271 *wl,
			    int index, bool enable,
			    struct wl12xx_rx_filter *filter)
{
	int ret;

	if (!!test_bit(index, wl->rx_filter_enabled) == enable) {
		wl1271_warning("Request to enable an already "
			     "enabled rx filter %d", index);
		return 0;
	}

	ret = wl1271_acx_set_rx_filter(wl, index, enable, filter);

	if (ret) {
		wl1271_error("Failed to %s rx data filter %d (err=%d)",
			     enable ? "enable" : "disable", index, ret);
		return ret;
	}

	if (enable)
		__set_bit(index, wl->rx_filter_enabled);
	else
		__clear_bit(index, wl->rx_filter_enabled);

	return 0;
}
