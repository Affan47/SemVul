dma_cycle (void)
{
	int hpos, hpos_old;

	blitter_nasty = 1;
	if (cpu_tracer  < 0)
		return current_hpos ();
	if (!currprefs.cpu_cycle_exact)
		return current_hpos ();
	while (currprefs.cpu_cycle_exact) {
		int bpldma;
		int blitpri = dmacon & DMA_BLITPRI;
		hpos_old = current_hpos ();
		hpos = hpos_old + 1;
		sync_copper (hpos);
		decide_line (hpos);
		decide_fetch_ce (hpos);
		bpldma = is_bitplane_dma (hpos_old);
		if (bltstate != BLT_done) {
			if (!blitpri && blitter_nasty >= BLIT_NASTY && (cycle_line[hpos_old] & CYCLE_MASK) == 0 && !bpldma) {
				alloc_cycle (hpos_old, CYCLE_CPUNASTY);
				break;
			}
			decide_blitter (hpos);

			sync_copper (hpos);
		}
		if ((cycle_line[hpos_old] & CYCLE_MASK) == 0 && !bpldma) {
			alloc_cycle (hpos_old, CYCLE_CPU);
			break;
		}
		regs.ce020memcycles -= CYCLE_UNIT;
		do_cycles (1 * CYCLE_UNIT);

	}
	return hpos_old;
}
