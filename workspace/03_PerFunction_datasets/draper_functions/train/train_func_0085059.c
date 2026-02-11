expamem_init_z3fastmem_2 (addrbank *bank, uae_u32 start, uae_u32 size, uae_u32 allocated)
{
	int code = (allocated == 0x100000 ? Z2_MEM_1MB
		: allocated == 0x200000 ? Z2_MEM_2MB
		: allocated == 0x400000 ? Z2_MEM_4MB
		: allocated == 0x800000 ? Z2_MEM_8MB
		: allocated == 0x1000000 ? Z3_MEM_16MB
		: allocated == 0x2000000 ? Z3_MEM_32MB
		: allocated == 0x4000000 ? Z3_MEM_64MB
		: allocated == 0x8000000 ? Z3_MEM_128MB
		: allocated == 0x10000000 ? Z3_MEM_256MB
		: allocated == 0x20000000 ? Z3_MEM_512MB
		: Z3_MEM_1GB);
	int subsize = (allocated == 0x100000 ? Z3_SS_MEM_1MB
		: allocated == 0x200000 ? Z3_SS_MEM_2MB
		: allocated == 0x400000 ? Z3_SS_MEM_4MB
		: allocated == 0x800000 ? Z3_SS_MEM_8MB
		: Z3_SS_MEM_SAME);

	if (allocated < 0x1000000)
		code = Z3_MEM_16MB;

	expamem_init_clear ();
	expamem_write (0x00, add_memory | zorroIII | code);

	expamem_write (0x08, care_addr | force_z3 | (allocated > 0x800000 ? ext_size : subsize));

	expamem_write (0x04, currprefs.maprom ? 3 : 83);

	expamem_write (0x10, uae_id >> 8);
	expamem_write (0x14, uae_id & 0xff);

	expamem_write (0x18, 0x00);
	expamem_write (0x1c, 0x00);
	expamem_write (0x20, 0x00);
	expamem_write (0x24, 0x01);

	expamem_write (0x28, 0x00);
	expamem_write (0x2c, 0x00);

	expamem_write (0x40, 0x00);

	map_banks (bank, start >> 16, size >> 16, allocated);

}
