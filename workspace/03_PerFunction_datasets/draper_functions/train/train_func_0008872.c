qlge_vlan_mode(struct net_device *ndev, netdev_features_t features)
{
	struct ql_adapter *qdev = netdev_priv(ndev);

	if (features & NETIF_F_HW_VLAN_CTAG_RX) {
		ql_write32(qdev, NIC_RCV_CFG, NIC_RCV_CFG_VLAN_MASK |
				 NIC_RCV_CFG_VLAN_MATCH_AND_NON);
	} else {
		ql_write32(qdev, NIC_RCV_CFG, NIC_RCV_CFG_VLAN_MASK);
	}
}
