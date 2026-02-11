ixgbe_blink_led_stop_generic(struct ixgbe_hw *hw, u32 index)
{
	u32 autoc_reg = 0;
	u32 led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
	bool locked = false;
	s32 ret_val;

	ret_val = hw->mac.ops.prot_autoc_read(hw, &locked, &autoc_reg);
	if (ret_val)
		return ret_val;

	autoc_reg &= ~IXGBE_AUTOC_FLU;
	autoc_reg |= IXGBE_AUTOC_AN_RESTART;

	ret_val = hw->mac.ops.prot_autoc_write(hw, autoc_reg, locked);
	if (ret_val)
		return ret_val;

	led_reg &= ~IXGBE_LED_MODE_MASK(index);
	led_reg &= ~IXGBE_LED_BLINK(index);
	led_reg |= IXGBE_LED_LINK_ACTIVE << IXGBE_LED_MODE_SHIFT(index);
	IXGBE_WRITE_REG(hw, IXGBE_LEDCTL, led_reg);
	IXGBE_WRITE_FLUSH(hw);

	return 0;
}
