ixgb_reset(struct ixgb_adapter *adapter)
{
	struct ixgb_hw *hw = &adapter->hw;

	ixgb_adapter_stop(hw);
	if (!ixgb_init_hw(hw))
		netif_err(adapter, probe, adapter->netdev, "ixgb_init_hw failed\n");


	IXGB_WRITE_REG(hw, MFS, hw->max_frame_size << IXGB_MFS_SHIFT);
	if (hw->max_frame_size >
	    IXGB_MAX_ENET_FRAME_SIZE_WITHOUT_FCS + ENET_FCS_LENGTH) {
		u32 ctrl0 = IXGB_READ_REG(hw, CTRL0);
		if (!(ctrl0 & IXGB_CTRL0_JFE)) {
			ctrl0 |= IXGB_CTRL0_JFE;
			IXGB_WRITE_REG(hw, CTRL0, ctrl0);
		}
	}
}
