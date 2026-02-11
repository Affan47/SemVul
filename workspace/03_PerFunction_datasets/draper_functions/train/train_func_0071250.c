do_cycles_ce (unsigned long cycles)
{
	unsigned long c;

	c = cycles + extra_cycle;
	while (c >= CYCLE_UNIT) {
		int hpos = current_hpos () + 1;
		sync_copper (hpos);
		decide_line (hpos);
		decide_fetch_ce (hpos);
		if (bltstate != BLT_done)
			decide_blitter (hpos);
		do_cycles (1 * CYCLE_UNIT);
		c -= CYCLE_UNIT;
	}
	extra_cycle = c;
}
