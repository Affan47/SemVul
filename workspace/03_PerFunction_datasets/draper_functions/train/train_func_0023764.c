m68k_resumestopped (void)
{
	if (!regs.stopped)
		return;
	regs.stopped = 0;
	if (currprefs.cpu_cycle_exact) {
		if (currprefs.cpu_model == 68000)
			x_do_cycles (6 * cpucycleunit);
	}
	fill_prefetch ();
	unset_special (SPCFLAG_STOP);
}
