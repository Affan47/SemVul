rt2500pci_config_intf(struct rt2x00_dev *rt2x00dev,
				  struct rt2x00_intf *intf,
				  struct rt2x00intf_conf *conf,
				  const unsigned int flags)
{
	struct data_queue *queue = rt2x00dev->bcn;
	unsigned int bcn_preload;
	u32 reg;

	if (flags & CONFIG_UPDATE_TYPE) {


		bcn_preload = PREAMBLE + GET_DURATION(IEEE80211_HEADER, 20);
		rt2x00mmio_register_read(rt2x00dev, BCNCSR1, &reg);
		rt2x00_set_field32(&reg, BCNCSR1_PRELOAD, bcn_preload);
		rt2x00_set_field32(&reg, BCNCSR1_BEACON_CWMIN, queue->cw_min);
		rt2x00mmio_register_write(rt2x00dev, BCNCSR1, reg);


		rt2x00mmio_register_read(rt2x00dev, CSR14, &reg);
		rt2x00_set_field32(&reg, CSR14_TSF_SYNC, conf->sync);
		rt2x00mmio_register_write(rt2x00dev, CSR14, reg);
	}

	if (flags & CONFIG_UPDATE_MAC)
		rt2x00mmio_register_multiwrite(rt2x00dev, CSR3,
					      conf->mac, sizeof(conf->mac));

	if (flags & CONFIG_UPDATE_BSSID)
		rt2x00mmio_register_multiwrite(rt2x00dev, CSR5,
					      conf->bssid, sizeof(conf->bssid));
}
