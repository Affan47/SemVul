wait_for_idle(struct aty128fb_par *par)
{
	int i;

	do_wait_for_fifo(64, par);

	for (;;) {
		for (i = 0; i < 2000000; i++) {
			if (!(aty_ld_le32(GUI_STAT) & (1 << 31))) {
				aty128_flush_pixel_cache(par);
				par->blitter_may_be_busy = 0;
				return;
			}
		}
		aty128_reset_engine(par);
	}
}
