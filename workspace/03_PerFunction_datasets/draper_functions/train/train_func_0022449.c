igb_get_cfg_done_82575(struct e1000_hw *hw)
{
	s32 timeout = PHY_CFG_TIMEOUT;
	s32 ret_val = E1000_SUCCESS;
	u32 mask = E1000_NVM_CFG_DONE_PORT_0;

	DEBUGFUNC("igb_get_cfg_done_82575");

	if (hw->bus.func == E1000_FUNC_1)
		mask = E1000_NVM_CFG_DONE_PORT_1;
	while (timeout) {
		if (E1000_READ_REG(hw, E1000_EEMNGCTL) & mask)
			break;
		msec_delay(1);
		timeout--;
	}
	if (!timeout) {
		DEBUGOUT("MNG configuration cycle has not completed.\n");
        }


	if (((E1000_READ_REG(hw, E1000_EECD) & E1000_EECD_PRES) == 0) &&
	    (hw->phy.type == e1000_phy_igp_3))
		igb_phy_init_script_igp3(hw);

	return ret_val;
}
