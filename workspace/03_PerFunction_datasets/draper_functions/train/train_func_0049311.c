wl12xx_scan_stop(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct wl1271_cmd_header *cmd = NULL;
	int ret = 0;

	if (WARN_ON(wl->scan.state == WL1271_SCAN_STATE_IDLE))
		return -EINVAL;

	wl1271_debug(DEBUG_CMD, "cmd scan stop");

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	ret = wl1271_cmd_send(wl, CMD_STOP_SCAN, cmd,
			      sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("cmd stop_scan failed");
		goto out;
	}
out:
	kfree(cmd);
	return ret;
}
