wl1271_acx_rx_msdu_life_time(struct wl1271 *wl)
{
	struct acx_rx_msdu_lifetime *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx rx msdu life time");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->lifetime = cpu_to_le32(wl->conf.rx.rx_msdu_life_time);
	ret = wl1271_cmd_configure(wl, DOT11_RX_MSDU_LIFE_TIME,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("failed to set rx msdu life time: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}
