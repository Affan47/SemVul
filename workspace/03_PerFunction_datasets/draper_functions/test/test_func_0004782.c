get_memory_io(word32 loc, double *cyc_ptr)
{
	int	tmp;

	if(loc > 0xffffff) {
		halt_printf("get_memory_io:%08x out of range==halt!\n", loc);
		return 0;
	}

	tmp = loc & 0xfef000;
	if(tmp == 0xc000 || tmp == 0xe0c000) {
		return(io_read(loc & 0xfff, cyc_ptr));
	}


	if(loc >= g_mem_size_total) {
		if((loc & 0xfffe) == 0) {
#if 0
			printf("get_io assuming mem sizing, not halting\n");
#endif
			return 0;
		}
	}


	if((loc & 0xf70000) == 0xf00000) {
		return 0;
	}

	if((loc & 0xff0000) == 0xef0000) {

		return (doc_ram[loc & 0xffff]);
	}

	g_code_yellow++;
	if(g_ignore_bad_acc && !g_user_halt_bad) {


		return 0;
	}

	printf("get_memory_io for addr: %06x\n", loc);
	printf("stat for addr: %06x = %p\n", loc,
				GET_PAGE_INFO_RD((loc >> 8) & 0xffff));
	set_halt(g_halt_on_bad_read | g_user_halt_bad);

	return 0;
}
