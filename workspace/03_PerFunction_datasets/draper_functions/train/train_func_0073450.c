BPLxDAT (int hpos, int num, uae_u16 v)
{

	if (num == 0 && hpos >= 7) {
		decide_line (hpos);
		decide_fetch (hpos);
	}
	bplxdat[num] = v;
	if (num == 0 && hpos >= 7) {
		bpl1dat_written = true;
		bpl1dat_written_at_least_once = true;
		if (thisline_decision.plfleft < 0) {
			thisline_decision.plfleft = hpos & ~3;
			reset_bpl_vars ();
			compute_delay_offset ();
		}
		update_bpldats (hpos);
	}
}
