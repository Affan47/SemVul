emulib_ChgSMemSize (uae_u32 memsize)
{
	if (memsize != 0x80000 && memsize != 0x100000 &&
		memsize != 0x180000 && memsize != 0x1C0000) {
			memsize = 0;
			write_log (_T("Unsupported bogomem size!\n"));
	}

	m68k_dreg (regs, 0) = 0;
	changed_prefs.bogomem_size = memsize;
	uae_reset (1, 1);
	return 1;
}
