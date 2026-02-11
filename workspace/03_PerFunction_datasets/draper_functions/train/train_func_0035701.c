ixgbe_poll_eerd_eewr_done(struct ixgbe_hw *hw, u32 ee_reg)
{
	u32 i;
	u32 reg;

	for (i = 0; i < IXGBE_EERD_EEWR_ATTEMPTS; i++) {
		if (ee_reg == IXGBE_NVM_POLL_READ)
			reg = IXGBE_READ_REG(hw, IXGBE_EERD);
		else
			reg = IXGBE_READ_REG(hw, IXGBE_EEWR);

		if (reg & IXGBE_EEPROM_RW_REG_DONE) {
			return 0;
		}
		udelay(5);
	}
	return IXGBE_ERR_EEPROM;
}
