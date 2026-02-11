expansion_init (void)
{
	if (savestate_state != STATE_RESTORE) {

		allocated_fastmem = 0;
		fastmem_mask = fastmem_start = 0;
		fastmemory = 0;

#ifdef PICASSO96
		allocated_gfxmem = 0;
		gfxmem_mask = gfxmem_start = 0;
		gfxmemory = 0;
#endif

#ifdef CATWEASEL
		catweasel_mask = catweasel_start = 0;
#endif

		allocated_z3fastmem = 0;
		z3fastmem_mask = z3fastmem_start = 0;
		z3fastmem = 0;
		allocated_z3fastmem2 = 0;
		z3fastmem2_mask = z3fastmem2_start = 0;
		z3fastmem2 = 0;
		allocated_z3chipmem = 0;
		z3chipmem_mask = z3chipmem_start = 0;
		z3chipmem = 0;
	}

#ifdef FILESYS
	filesys_start = 0;
	filesysory = 0;
#endif

	allocate_expamem ();

#ifdef FILESYS
	filesysory = mapped_malloc (0x10000, _T("filesys"));
	if (!filesysory) {
		write_log (_T("virtual memory exhausted (filesysory)!\n"));
		exit (0);
	}
	filesys_bank.baseaddr = filesysory;
#endif
}
