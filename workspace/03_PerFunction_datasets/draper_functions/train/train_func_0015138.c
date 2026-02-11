sw_cfg(struct ksz_hw *hw, u32 addr, u16 bits, int set)
{
	u16 data;

	data = readw(hw->io + addr);
	if (set)
		data |= bits;
	else
		data &= ~bits;
	writew(data, hw->io + addr);
}
