fixup_shadow_shr()
{
	byte	*mem0wr;
	int	j;


	mem0wr = &(g_memory_ptr[0x00000]);
	if(RAMWRT) {
		mem0wr += 0x10000;
		if((g_c035_shadow_reg & 0x8) == 0) {
			mem0wr += BANK_SHADOW2;
		}
	}
	for(j = 0x60; j < 0xa0; j++) {
		SET_PAGE_INFO_WR(j, mem0wr + j*0x100);
	}


	mem0wr = &(g_memory_ptr[0x10000]);
	if((g_c035_shadow_reg & 0x8) == 0) {
		mem0wr += BANK_SHADOW2;
	}
	for(j = 0x60; j < 0xa0; j++) {
		SET_PAGE_INFO_WR(0x100 + j, mem0wr + j*0x100);
	}
}
