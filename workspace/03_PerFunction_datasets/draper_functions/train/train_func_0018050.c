wil_ethtoolops_set_coalesce(struct net_device *ndev,
				       struct ethtool_coalesce *cp)
{
	struct wil6210_priv *wil = ndev_to_wil(ndev);

	wil_dbg_misc(wil, "%s(rx %d usec, tx %d usec)\n", __func__,
		     cp->rx_coalesce_usecs, cp->tx_coalesce_usecs);

	if (wil->wdev->iftype == NL80211_IFTYPE_MONITOR) {
		wil_dbg_misc(wil, "No IRQ coalescing in monitor mode\n");
		return -EINVAL;
	}


	if (cp->rx_coalesce_usecs > WIL6210_ITR_TRSH_MAX ||
	    cp->tx_coalesce_usecs > WIL6210_ITR_TRSH_MAX)
		goto out_bad;

	wil->tx_max_burst_duration = cp->tx_coalesce_usecs;
	wil->rx_max_burst_duration = cp->rx_coalesce_usecs;
	wil_configure_interrupt_moderation(wil);

	return 0;

out_bad:
	wil_dbg_misc(wil, "Unsupported coalescing params. Raw command:\n");
	print_hex_dump_debug("DBG[MISC] coal ", DUMP_PREFIX_OFFSET, 16, 4,
			     cp, sizeof(*cp), false);
	return -EINVAL;
}
