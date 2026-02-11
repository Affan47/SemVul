nes_init_phy(struct nes_device *nesdev)
{
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	u32 mac_index = nesdev->mac_index;
	u32 tx_config = 0;
	unsigned long flags;
	u8  phy_type = nesadapter->phy_type[mac_index];
	u8  phy_index = nesadapter->phy_index[mac_index];
	int ret = 0;

	tx_config = nes_read_indexed(nesdev, NES_IDX_MAC_TX_CONFIG);
	if (phy_type == NES_PHY_TYPE_1G) {

		tx_config &= 0xFFFFFFE3;
		tx_config |= 0x04;
	} else {

		tx_config &= 0xFFFFFFE3;
		tx_config |= 0x1D;
	}
	nes_write_indexed(nesdev, NES_IDX_MAC_TX_CONFIG, tx_config);

	spin_lock_irqsave(&nesdev->nesadapter->phy_lock, flags);

	switch (phy_type) {
	case NES_PHY_TYPE_1G:
		ret = nes_init_1g_phy(nesdev, phy_type, phy_index);
		break;
	case NES_PHY_TYPE_ARGUS:
	case NES_PHY_TYPE_SFP_D:
	case NES_PHY_TYPE_KR:
		ret = nes_init_2025_phy(nesdev, phy_type, phy_index);
		break;
	}

	spin_unlock_irqrestore(&nesdev->nesadapter->phy_lock, flags);

	return ret;
}
