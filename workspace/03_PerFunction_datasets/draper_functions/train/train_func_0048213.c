hns_dsaf_get_mac_mc_entry(struct dsaf_device *dsaf_dev,
			      struct dsaf_drv_mac_multi_dest_entry *mac_entry)
{
	u16 entry_index = DSAF_INVALID_ENTRY_IDX;
	struct dsaf_drv_tbl_tcam_key mac_key;

	struct dsaf_tbl_tcam_mcast_cfg mac_data;


	if (MAC_IS_ALL_ZEROS(mac_entry->addr) ||
	    MAC_IS_BROADCAST(mac_entry->addr)) {
		dev_err(dsaf_dev->dev, "get_entry failed,addr %pM\n",
			mac_entry->addr);
		return -EINVAL;
	}


	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, mac_entry->in_vlan_id,
			     mac_entry->in_port_num, mac_entry->addr);


	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	if (entry_index == DSAF_INVALID_ENTRY_IDX) {

		dev_err(dsaf_dev->dev,
			"get_mac_uc_entry failed, %s Mac key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, mac_key.high.val,
			mac_key.low.val);
		return -EINVAL;
	}
	dev_dbg(dsaf_dev->dev,
		"get_mac_uc_entry, %s Mac key(%#x:%#x) entry_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.val,
		mac_key.low.val, entry_index);


	hns_dsaf_tcam_mc_get(dsaf_dev, entry_index,
			     (struct dsaf_tbl_tcam_data *)&mac_key, &mac_data);

	mac_entry->port_mask[0] = mac_data.tbl_mcast_port_msk[0] & 0x3F;
	return 0;
}
