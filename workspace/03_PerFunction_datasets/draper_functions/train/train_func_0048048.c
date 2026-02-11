ixgbe_clock_in_i2c_byte(struct ixgbe_hw *hw, u8 *data)
{
	s32 i;
	bool bit = false;

	*data = 0;
	for (i = 7; i >= 0; i--) {
		ixgbe_clock_in_i2c_bit(hw, &bit);
		*data |= bit << i;
	}

	return 0;
}
