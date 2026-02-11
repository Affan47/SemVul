igb_release_hw_control(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl_ext;


	ctrl_ext = rd32(E1000_CTRL_EXT);
	wr32(E1000_CTRL_EXT,
			ctrl_ext & ~E1000_CTRL_EXT_DRV_LOAD);
}
