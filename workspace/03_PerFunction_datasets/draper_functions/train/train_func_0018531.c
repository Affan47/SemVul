custom_bput (uaecptr addr, uae_u32 value)
{
	static int warned;
	uae_u16 rval;

	if (currprefs.chipset_mask & CSMASK_AGA) {
		if (addr & 1) {
			rval = value & 0xff;
		} else {
			rval = (value << 8) | (value & 0xFF);
		}
	} else {
		rval = (value << 8) | (value & 0xff);
	}

#ifdef JIT
	special_mem |= S_WRITE;
#endif
	if (currprefs.cpu_model == 68060) {
		if (addr & 1)
			custom_wput (addr & ~1, rval);
		else
			custom_wput (addr, value << 8);
	} else {
		custom_wput (addr & ~1, rval);
	}
}
