e1000_write_flash_data_ich8lan(struct e1000_hw *hw, u32 offset,
					  u8 size, u16 data)
{
	union ich8_hws_flash_status hsfsts;
	union ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	u32 flash_data = 0;
	s32 ret_val;
	u8 count = 0;

	if (hw->mac.type == e1000_pch_spt) {
		if (size != 4 || offset > ICH_FLASH_LINEAR_ADDR_MASK)
			return -E1000_ERR_NVM;
	} else {
		if (size < 1 || size > 2 || offset > ICH_FLASH_LINEAR_ADDR_MASK)
			return -E1000_ERR_NVM;
	}

	flash_linear_addr = ((ICH_FLASH_LINEAR_ADDR_MASK & offset) +
			     hw->nvm.flash_base_addr);

	do {
		udelay(1);

		ret_val = e1000_flash_cycle_init_ich8lan(hw);
		if (ret_val)
			break;


		if (hw->mac.type == e1000_pch_spt)
			hsflctl.regval = er32flash(ICH_FLASH_HSFSTS) >> 16;
		else
			hsflctl.regval = er16flash(ICH_FLASH_HSFCTL);


		hsflctl.hsf_ctrl.fldbcount = size - 1;
		hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_WRITE;


		if (hw->mac.type == e1000_pch_spt)
			ew32flash(ICH_FLASH_HSFSTS, hsflctl.regval << 16);
		else
			ew16flash(ICH_FLASH_HSFCTL, hsflctl.regval);

		ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

		if (size == 1)
			flash_data = (u32)data & 0x00FF;
		else
			flash_data = (u32)data;

		ew32flash(ICH_FLASH_FDATA0, flash_data);


		ret_val =
		    e1000_flash_cycle_ich8lan(hw,
					      ICH_FLASH_WRITE_COMMAND_TIMEOUT);
		if (!ret_val)
			break;


		hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
		if (hsfsts.hsf_status.flcerr)

			continue;
		if (!hsfsts.hsf_status.flcdone) {
			e_dbg("Timeout error - flash cycle did not complete.\n");
			break;
		}
	} while (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

	return ret_val;
}
