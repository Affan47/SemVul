ixgbe_write_eeprom_generic(struct ixgbe_hw *hw, u16 offset, u16 data)
{
	hw->eeprom.ops.init_params(hw);

	if (offset >= hw->eeprom.word_size)
		return IXGBE_ERR_EEPROM;

	return ixgbe_write_eeprom_buffer_bit_bang(hw, offset, 1, &data);
}
