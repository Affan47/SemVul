hns_ae_set_pauseparam(struct hnae_handle *handle,
				 u32 autoneg, u32 rx_en, u32 tx_en)
{
	struct hns_mac_cb *mac_cb = hns_get_mac_cb(handle);
	int ret;

	ret = hns_mac_set_autoneg(mac_cb, autoneg);
	if (ret)
		return ret;

	return hns_mac_set_pauseparam(mac_cb, rx_en, tx_en);
}
