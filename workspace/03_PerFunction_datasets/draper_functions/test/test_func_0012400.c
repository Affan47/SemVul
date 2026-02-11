atl1c_start_mac(struct atl1c_adapter *adapter)
{
	struct atl1c_hw *hw = &adapter->hw;
	u32 mac, txq, rxq;

	hw->mac_duplex = adapter->link_duplex == FULL_DUPLEX ? true : false;
	hw->mac_speed = adapter->link_speed == SPEED_1000 ?
		atl1c_mac_speed_1000 : atl1c_mac_speed_10_100;

	AT_READ_REG(hw, REG_TXQ_CTRL, &txq);
	AT_READ_REG(hw, REG_RXQ_CTRL, &rxq);
	AT_READ_REG(hw, REG_MAC_CTRL, &mac);

	txq |= TXQ_CTRL_EN;
	rxq |= RXQ_CTRL_EN;
	mac |= MAC_CTRL_TX_EN | MAC_CTRL_TX_FLOW |
	       MAC_CTRL_RX_EN | MAC_CTRL_RX_FLOW |
	       MAC_CTRL_ADD_CRC | MAC_CTRL_PAD |
	       MAC_CTRL_BC_EN | MAC_CTRL_SINGLE_PAUSE_EN |
	       MAC_CTRL_HASH_ALG_CRC32;
	if (hw->mac_duplex)
		mac |= MAC_CTRL_DUPLX;
	else
		mac &= ~MAC_CTRL_DUPLX;
	mac = FIELD_SETX(mac, MAC_CTRL_SPEED, hw->mac_speed);
	mac = FIELD_SETX(mac, MAC_CTRL_PRMLEN, hw->preamble_len);

	AT_WRITE_REG(hw, REG_TXQ_CTRL, txq);
	AT_WRITE_REG(hw, REG_RXQ_CTRL, rxq);
	AT_WRITE_REG(hw, REG_MAC_CTRL, mac);
}
