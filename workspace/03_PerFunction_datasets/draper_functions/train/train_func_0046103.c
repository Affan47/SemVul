spi_reg(struct ksz_hw *hw, u8 data, u8 reg)
{
	int i;


	raise_gpio(hw, EEPROM_DATA_OUT);
	eeprom_clk(hw);


	for (i = 1; i >= 0; i--) {
		(data & (0x01 << i)) ? raise_gpio(hw, EEPROM_DATA_OUT) :
			drop_gpio(hw, EEPROM_DATA_OUT);
		eeprom_clk(hw);
	}


	for (i = 5; i >= 0; i--) {
		(reg & (0x01 << i)) ? raise_gpio(hw, EEPROM_DATA_OUT) :
			drop_gpio(hw, EEPROM_DATA_OUT);
		eeprom_clk(hw);
	}
}
