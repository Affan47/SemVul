atl1e_xmit_frame(struct net_device *netdev, struct io_buffer *iob)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);
	u16 tpd_req = 1;
	struct atl1e_tpd_desc *tpd;

	if (!netdev_link_ok(netdev)) {
		return -EINVAL;
	}

	if (atl1e_tpd_avail(adapter) < tpd_req) {
		return -EBUSY;
	}

	tpd = atl1e_get_tpd(adapter);

	atl1e_tx_map(adapter, iob, tpd);
	atl1e_tx_queue(adapter, tpd_req, tpd);

	return 0;
}
