spi_w(struct ksz_hw *hw, u16 data)
{
	int i;

	for (i = 15; i >= 0; i--) {
		(data & (0x01 << i)) ? raise_gpio(hw, EEPROM_DATA_OUT) :
			drop_gpio(hw, EEPROM_DATA_OUT);
		eeprom_clk(hw);
	}
}
