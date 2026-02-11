flip_4bit(u16 value)
{
	u16 flipped = 0x0000;

	B43legacy_BUG_ON(!((value & ~0x000F) == 0x0000));

	flipped |= (value & 0x0001) << 3;
	flipped |= (value & 0x0002) << 1;
	flipped |= (value & 0x0004) >> 1;
	flipped |= (value & 0x0008) >> 3;

	return flipped;
}
