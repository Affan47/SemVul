ixgbe_update_eeprom_checksum_generic(struct ixgbe_hw *hw)
{
	s32 status;
	u16 checksum;


	status = hw->eeprom.ops.read(hw, 0, &checksum);
	if (status) {
		hw_dbg(hw, "EEPROM read failed\n");
		return status;
	}

	status = hw->eeprom.ops.calc_checksum(hw);
	if (status < 0)
		return status;

	checksum = (u16)(status & 0xffff);

	status = hw->eeprom.ops.write(hw, IXGBE_EEPROM_CHECKSUM, checksum);

	return status;
}
