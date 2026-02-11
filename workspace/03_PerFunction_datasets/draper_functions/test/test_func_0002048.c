mon_mgmt_tx(struct net_device *dev, const u8 *buf, size_t len)
{
	struct tx_complete_mon_data *mgmt_tx = NULL;

	if (dev == NULL) {
		PRINT_D(HOSTAPD_DBG, "ERROR: dev == NULL\n");
		return -EFAULT;
	}

	netif_stop_queue(dev);
	mgmt_tx = kmalloc(sizeof(struct tx_complete_mon_data), GFP_ATOMIC);
	if (mgmt_tx == NULL) {
		PRINT_ER("Failed to allocate memory for mgmt_tx structure\n");
		return -EFAULT;
	}

	mgmt_tx->buff = kmalloc(len, GFP_ATOMIC);
	if (mgmt_tx->buff == NULL) {
		PRINT_ER("Failed to allocate memory for mgmt_tx buff\n");
		kfree(mgmt_tx);
		return -EFAULT;

	}

	mgmt_tx->size = len;

	memcpy(mgmt_tx->buff, buf, len);
	wilc_wlan_txq_add_mgmt_pkt(mgmt_tx, mgmt_tx->buff, mgmt_tx->size,
				   mgmt_tx_complete);

	netif_wake_queue(dev);
	return 0;
}
