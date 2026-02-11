_rtl8821ae_get_rate_section_index(u32 regaddr)
{
	u8 index = 0;
	regaddr &= 0xFFF;
	if (regaddr >= 0xC20 && regaddr <= 0xC4C)
		index = (u8)((regaddr - 0xC20) / 4);
	else if (regaddr >= 0xE20 && regaddr <= 0xE4C)
		index = (u8)((regaddr - 0xE20) / 4);
	else
		RT_ASSERT(!COMP_INIT,
			  "Invalid RegAddr 0x%x\n", regaddr);
	return index;
}
