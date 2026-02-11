mwifiex_cfg80211_set_wiphy_params(struct wiphy *wiphy, u32 changed)
{
	struct mwifiex_adapter *adapter = mwifiex_cfg80211_get_adapter(wiphy);
	struct mwifiex_private *priv;
	struct mwifiex_uap_bss_param *bss_cfg;
	int ret;

	priv = mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	switch (priv->bss_role) {
	case MWIFIEX_BSS_ROLE_UAP:
		if (priv->bss_started) {
			mwifiex_dbg(adapter, ERROR,
				    "cannot change wiphy params when bss started");
			return -EINVAL;
		}

		bss_cfg = kzalloc(sizeof(*bss_cfg), GFP_KERNEL);
		if (!bss_cfg)
			return -ENOMEM;

		mwifiex_set_sys_config_invalid_data(bss_cfg);

		if (changed & WIPHY_PARAM_RTS_THRESHOLD)
			bss_cfg->rts_threshold = wiphy->rts_threshold;
		if (changed & WIPHY_PARAM_FRAG_THRESHOLD)
			bss_cfg->frag_threshold = wiphy->frag_threshold;
		if (changed & WIPHY_PARAM_RETRY_LONG)
			bss_cfg->retry_limit = wiphy->retry_long;

		ret = mwifiex_send_cmd(priv, HostCmd_CMD_UAP_SYS_CONFIG,
				       HostCmd_ACT_GEN_SET,
				       UAP_BSS_PARAMS_I, bss_cfg,
				       false);

		kfree(bss_cfg);
		if (ret) {
			mwifiex_dbg(adapter, ERROR,
				    "Failed to set wiphy phy params\n");
			return ret;
		}
		break;

		case MWIFIEX_BSS_ROLE_STA:
		if (priv->media_connected) {
			mwifiex_dbg(adapter, ERROR,
				    "cannot change wiphy params when connected");
			return -EINVAL;
		}
		if (changed & WIPHY_PARAM_RTS_THRESHOLD) {
			ret = mwifiex_set_rts(priv,
					      wiphy->rts_threshold);
			if (ret)
				return ret;
		}
		if (changed & WIPHY_PARAM_FRAG_THRESHOLD) {
			ret = mwifiex_set_frag(priv,
					       wiphy->frag_threshold);
			if (ret)
				return ret;
		}
		break;
	}

	return 0;
}
