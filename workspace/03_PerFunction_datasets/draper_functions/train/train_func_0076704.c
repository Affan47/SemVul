vblank_callback(int scanline)
{
	vblank_count++;

	logerror("---- vblank\n");


	if (swaps_pending && vblank_count > vblanks_before_swap)
	{
		vblank_count = 0;
		swaps_pending--;
		swap_buffers();

		if (blocked_on_swap)
			blocked_on_swap = 0;
	}


	timer_adjust(vblank_timer, cpu_getscanlinetime(scanline), scanline, 0);
}
