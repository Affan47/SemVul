__cxgb_close(struct net_device *dev, int on_wq)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;


	if (!adapter->open_device_map)
		return 0;


	t3_xgm_intr_disable(adapter, pi->port_id);
	t3_read_reg(adapter, A_XGM_INT_STATUS + pi->mac.offset);

	t3_port_intr_disable(adapter, pi->port_id);
	netif_tx_stop_all_queues(dev);
	pi->phy.ops->power_down(&pi->phy, 1);
	netif_carrier_off(dev);
	t3_mac_disable(&pi->mac, MAC_DIRECTION_TX | MAC_DIRECTION_RX);

	spin_lock_irq(&adapter->work_lock);
	clear_bit(pi->port_id, &adapter->open_device_map);
	spin_unlock_irq(&adapter->work_lock);

	if (!(adapter->open_device_map & PORT_MASK))
		cancel_delayed_work_sync(&adapter->adap_check_task);

	if (!adapter->open_device_map)
		cxgb_down(adapter, on_wq);

	cxgb3_event_notify(&adapter->tdev, OFFLOAD_PORT_DOWN, pi->port_id);
	return 0;
}
