wl1271_acx_ap_rate_policy(struct wl1271 *wl, struct conf_tx_rate_class *c,
		      u8 idx)
{
	struct acx_rate_policy *acx;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx ap rate policy %d rates 0x%x",
		     idx, c->enabled_rates);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->rate_policy.enabled_rates = cpu_to_le32(c->enabled_rates);
	acx->rate_policy.short_retry_limit = c->short_retry_limit;
	acx->rate_policy.long_retry_limit = c->long_retry_limit;
	acx->rate_policy.aflags = c->aflags;

	acx->rate_policy_idx = cpu_to_le32(idx);

	ret = wl1271_cmd_configure(wl, ACX_RATE_POLICY, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("Setting of ap rate policy failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}
