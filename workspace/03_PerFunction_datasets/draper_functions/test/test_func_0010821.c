arb_wput (uaecptr addr, uae_u32 w)
{
	uae_u16 *m;

	addr -= arb_start & arb_mask;
	addr &= arb_mask;
	if (addr >= nvram_offset) {
		m = (uae_u16 *)(arbmemory + addr);
		do_put_mem_word (m, w);
		nvwrite++;
		if (addr == 0x1ffffe)
			multigame(w);
	}
}
