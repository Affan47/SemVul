NVReadAttr(struct nvidia_par *par, u8 index)
{
	volatile u8 tmp;

	tmp = VGA_RD08(par->PCIO, par->IOBase + 0x0a);
	if (par->paletteEnabled)
		index &= ~0x20;
	else
		index |= 0x20;
	VGA_WR08(par->PCIO, VGA_ATT_IW, index);
	return (VGA_RD08(par->PCIO, VGA_ATT_R));
}
