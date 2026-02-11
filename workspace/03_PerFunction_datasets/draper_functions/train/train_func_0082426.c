setclr (uae_u16 *p, uae_u16 val)
{
	if (val & 0x8000)
		*p |= val & 0x7FFF;
	else
		*p &= ~val;
}
