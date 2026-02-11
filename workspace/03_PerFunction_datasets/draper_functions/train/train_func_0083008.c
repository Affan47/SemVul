atl1c_restore_vlan(struct atl1c_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;

	if (netif_msg_pktdata(adapter))
		dev_dbg(&pdev->dev, "atl1c_restore_vlan\n");
	atl1c_vlan_mode(adapter->netdev, adapter->netdev->features);
}
