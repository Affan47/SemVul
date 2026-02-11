at76_dump_mib_mac_mgmt(struct at76_priv *priv)
{
	int ret;
	struct mib_mac_mgmt *m = kmalloc(sizeof(struct mib_mac_mgmt),
					 GFP_KERNEL);

	if (!m)
		return;

	ret = at76_get_mib(priv->udev, MIB_MAC_MGMT, m,
			   sizeof(struct mib_mac_mgmt));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MAC_MGMT) failed: %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MAC_MGMT: beacon_period %d CFP_max_duration "
		 "%d medium_occupancy_limit %d station_id 0x%x ATIM_window %d "
		 "CFP_mode %d privacy_opt_impl %d DTIM_period %d CFP_period %d "
		 "current_bssid %pM current_essid %*phD current_bss_type %d "
		 "pm_mode %d ibss_change %d res %d "
		 "multi_domain_capability_implemented %d "
		 "international_roaming %d country_string %.3s",
		 wiphy_name(priv->hw->wiphy), le16_to_cpu(m->beacon_period),
		 le16_to_cpu(m->CFP_max_duration),
		 le16_to_cpu(m->medium_occupancy_limit),
		 le16_to_cpu(m->station_id), le16_to_cpu(m->ATIM_window),
		 m->CFP_mode, m->privacy_option_implemented, m->DTIM_period,
		 m->CFP_period, m->current_bssid,
		 IW_ESSID_MAX_SIZE, m->current_essid,
		 m->current_bss_type, m->power_mgmt_mode, m->ibss_change,
		 m->res, m->multi_domain_capability_implemented,
		 m->multi_domain_capability_enabled, m->country_string);
exit:
	kfree(m);
}
