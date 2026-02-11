igb_ready_nvm_eeprom(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = E1000_READ_REG(hw, E1000_EECD);
	s32 ret_val = E1000_SUCCESS;
	u16 timeout = 0;
	u8 spi_stat_reg;

	DEBUGFUNC("igb_ready_nvm_eeprom");

	if (nvm->type == e1000_nvm_eeprom_spi) {

		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		E1000_WRITE_REG(hw, E1000_EECD, eecd);
		usec_delay(1);
		timeout = NVM_MAX_RETRY_SPI;


		while (timeout) {
			igb_shift_out_eec_bits(hw, NVM_RDSR_OPCODE_SPI,
			                         hw->nvm.opcode_bits);
			spi_stat_reg = (u8)igb_shift_in_eec_bits(hw, 8);
			if (!(spi_stat_reg & NVM_STATUS_RDY_SPI))
				break;

			usec_delay(5);
			igb_standby_nvm(hw);
			timeout--;
		}

		if (!timeout) {
			DEBUGOUT("SPI NVM Status error\n");
			ret_val = -E1000_ERR_NVM;
			goto out;
		}
	}

out:
	return ret_val;
}
