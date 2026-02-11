atl1c_set_multi(struct net_device *netdev)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	struct atl1c_hw *hw = &adapter->hw;
	struct netdev_hw_addr *ha;
	u32 mac_ctrl_data;
	u32 hash_value;


	AT_READ_REG(hw, REG_MAC_CTRL, &mac_ctrl_data);

	if (netdev->flags & IFF_PROMISC) {
		mac_ctrl_data |= MAC_CTRL_PROMIS_EN;
	} else if (netdev->flags & IFF_ALLMULTI) {
		mac_ctrl_data |= MAC_CTRL_MC_ALL_EN;
		mac_ctrl_data &= ~MAC_CTRL_PROMIS_EN;
	} else {
		mac_ctrl_data &= ~(MAC_CTRL_PROMIS_EN | MAC_CTRL_MC_ALL_EN);
	}

	AT_WRITE_REG(hw, REG_MAC_CTRL, mac_ctrl_data);


	AT_WRITE_REG(hw, REG_RX_HASH_TABLE, 0);
	AT_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, 1, 0);


	netdev_for_each_mc_addr(ha, netdev) {
		hash_value = atl1c_hash_mc_addr(hw, ha->addr);
		atl1c_hash_set(hw, hash_value);
	}
}
