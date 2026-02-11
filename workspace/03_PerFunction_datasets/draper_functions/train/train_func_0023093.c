hns_dsaf_find_soft_mac_entry(
	struct dsaf_device *dsaf_dev,
	struct dsaf_drv_tbl_tcam_key *mac_key)
{
	struct dsaf_drv_priv *priv =
	    (struct dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);
	struct dsaf_drv_soft_mac_tbl *soft_mac_entry;
	u32 i;

	soft_mac_entry = priv->soft_mac_tbl;
	for (i = 0; i < DSAF_TCAM_SUM; i++) {

		if ((soft_mac_entry->index != DSAF_INVALID_ENTRY_IDX) &&
		    (soft_mac_entry->tcam_key.high.val == mac_key->high.val) &&
		    (soft_mac_entry->tcam_key.low.val == mac_key->low.val))

			return soft_mac_entry->index;

		soft_mac_entry++;
	}
	return DSAF_INVALID_ENTRY_IDX;
}
