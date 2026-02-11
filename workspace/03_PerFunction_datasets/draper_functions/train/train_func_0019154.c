atl1c_vlan_mode(struct net_device *netdev,
	netdev_features_t features)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	struct pci_dev *pdev = adapter->pdev;
	u32 mac_ctrl_data = 0;

	if (netif_msg_pktdata(adapter))
		dev_dbg(&pdev->dev, "atl1c_vlan_mode\n");

	atl1c_irq_disable(adapter);
	AT_READ_REG(&adapter->hw, REG_MAC_CTRL, &mac_ctrl_data);
	__atl1c_vlan_mode(features, &mac_ctrl_data);
	AT_WRITE_REG(&adapter->hw, REG_MAC_CTRL, mac_ctrl_data);
	atl1c_irq_enable(adapter);
}
