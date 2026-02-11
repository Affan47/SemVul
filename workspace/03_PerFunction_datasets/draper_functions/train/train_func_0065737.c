__e1000_read_kmrn_reg(struct e1000_hw *hw, u32 offset, u16 *data,
				 bool locked)
{
	u32 kmrnctrlsta;

	if (!locked) {
		s32 ret_val = 0;

		if (!hw->phy.ops.acquire)
			return 0;

		ret_val = hw->phy.ops.acquire(hw);
		if (ret_val)
			return ret_val;
	}

	kmrnctrlsta = ((offset << E1000_KMRNCTRLSTA_OFFSET_SHIFT) &
		       E1000_KMRNCTRLSTA_OFFSET) | E1000_KMRNCTRLSTA_REN;
	ew32(KMRNCTRLSTA, kmrnctrlsta);
	e1e_flush();

	udelay(2);

	kmrnctrlsta = er32(KMRNCTRLSTA);
	*data = (u16)kmrnctrlsta;

	if (!locked)
		hw->phy.ops.release(hw);

	return 0;
}
