e1000_valid_nvm_bank_detect_ich8lan(struct e1000_hw *hw, u32 *bank)
{
	u32 eecd;
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 bank1_offset = nvm->flash_bank_size * sizeof(u16);
	u32 act_offset = E1000_ICH_NVM_SIG_WORD * 2 + 1;
	u32 nvm_dword = 0;
	u8 sig_byte = 0;
	s32 ret_val;

	switch (hw->mac.type) {
	case e1000_pch_spt:
		bank1_offset = nvm->flash_bank_size;
		act_offset = E1000_ICH_NVM_SIG_WORD;


		*bank = 0;


		ret_val = e1000_read_flash_dword_ich8lan(hw, act_offset,
							 &nvm_dword);
		if (ret_val)
			return ret_val;
		sig_byte = (u8)((nvm_dword & 0xFF00) >> 8);
		if ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) {
			*bank = 0;
			return 0;
		}


		ret_val = e1000_read_flash_dword_ich8lan(hw, act_offset +
							 bank1_offset,
							 &nvm_dword);
		if (ret_val)
			return ret_val;
		sig_byte = (u8)((nvm_dword & 0xFF00) >> 8);
		if ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) {
			*bank = 1;
			return 0;
		}

		e_dbg("ERROR: No valid NVM bank present\n");
		return -E1000_ERR_NVM;
	case e1000_ich8lan:
	case e1000_ich9lan:
		eecd = er32(EECD);
		if ((eecd & E1000_EECD_SEC1VAL_VALID_MASK) ==
		    E1000_EECD_SEC1VAL_VALID_MASK) {
			if (eecd & E1000_EECD_SEC1VAL)
				*bank = 1;
			else
				*bank = 0;

			return 0;
		}
		e_dbg("Unable to determine valid NVM bank via EEC - reading flash signature\n");

	default:

		*bank = 0;


		ret_val = e1000_read_flash_byte_ich8lan(hw, act_offset,
							&sig_byte);
		if (ret_val)
			return ret_val;
		if ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) {
			*bank = 0;
			return 0;
		}


		ret_val = e1000_read_flash_byte_ich8lan(hw, act_offset +
							bank1_offset,
							&sig_byte);
		if (ret_val)
			return ret_val;
		if ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) {
			*bank = 1;
			return 0;
		}

		e_dbg("ERROR: No valid NVM bank present\n");
		return -E1000_ERR_NVM;
	}
}
