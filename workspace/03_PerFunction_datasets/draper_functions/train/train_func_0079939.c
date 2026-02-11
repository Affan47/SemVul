ixgbe_ready_eeprom(struct ixgbe_hw *hw)
{
	u16 i;
	u8 spi_stat_reg;


	for (i = 0; i < IXGBE_EEPROM_MAX_RETRY_SPI; i += 5) {
		ixgbe_shift_out_eeprom_bits(hw, IXGBE_EEPROM_RDSR_OPCODE_SPI,
					    IXGBE_EEPROM_OPCODE_BITS);
		spi_stat_reg = (u8)ixgbe_shift_in_eeprom_bits(hw, 8);
		if (!(spi_stat_reg & IXGBE_EEPROM_STATUS_RDY_SPI))
			break;

		udelay(5);
		ixgbe_standby_eeprom(hw);
	}


	if (i >= IXGBE_EEPROM_MAX_RETRY_SPI) {
		hw_dbg(hw, "SPI EEPROM Status error\n");
		return IXGBE_ERR_EEPROM;
	}

	return 0;
}
