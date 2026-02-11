load_kickstart_replacement (void)
{
	struct zfile *f;

	f = zfile_fopen_data (_T("aros.gz"), arosrom_len, arosrom);
	if (!f)
		return false;
	f = zfile_gunzip (f);
	if (!f)
		return false;
	kickmem_mask = 0x80000 - 1;
	kickmem_size = 0x80000;
	extendedkickmem_size = 0x80000;
	extendedkickmem_type = EXTENDED_ROM_KS;
	extendedkickmemory = mapped_malloc (extendedkickmem_size, _T("rom_e0"));
	extendedkickmem_bank.baseaddr = extendedkickmemory;
	read_kickstart (f, extendedkickmemory, extendedkickmem_size, 0, 1);
	extendedkickmem_mask = extendedkickmem_size - 1;
	read_kickstart (f, kickmemory, 0x80000, 1, 0);
	zfile_fclose (f);
	seriallog = -1;
	return true;
}
