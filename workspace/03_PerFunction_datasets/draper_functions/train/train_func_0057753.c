e1000_read_flash_data32_ich8lan(struct e1000_hw *hw, u32 offset,
					   u32 *data)
{
	union ich8_hws_flash_status hsfsts;
	union ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	s32 ret_val = -E1000_ERR_NVM;
	u8 count = 0;

	if (offset > ICH_FLASH_LINEAR_ADDR_MASK ||
	    hw->mac.type != e1000_pch_spt)
		return -E1000_ERR_NVM;
	flash_linear_addr = ((ICH_FLASH_LINEAR_ADDR_MASK & offset) +
			     hw->nvm.flash_base_addr);

	do {
		udelay(1);

		ret_val = e1000_flash_cycle_init_ich8lan(hw);
		if (ret_val)
			break;


		hsflctl.regval = er32flash(ICH_FLASH_HSFSTS) >> 16;


		hsflctl.hsf_ctrl.fldbcount = sizeof(u32) - 1;
		hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_READ;


		ew32flash(ICH_FLASH_HSFSTS, (u32)hsflctl.regval << 16);
		ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

		ret_val =
		   e1000_flash_cycle_ich8lan(hw,
					     ICH_FLASH_READ_COMMAND_TIMEOUT);


		if (!ret_val) {
			*data = er32flash(ICH_FLASH_FDATA0);
			break;
		} else {


			hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
			if (hsfsts.hsf_status.flcerr) {

				continue;
			} else if (!hsfsts.hsf_status.flcdone) {
				e_dbg("Timeout error - flash cycle did not complete.\n");
				break;
			}
		}
	} while (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

	return ret_val;
}
