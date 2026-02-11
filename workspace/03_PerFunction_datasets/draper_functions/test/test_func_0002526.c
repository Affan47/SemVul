cave_vblank_end(int param)
{
	if(cave_kludge == 3)
	{
		unknown_irq = 1;
		update_irq_state();
	}
	agallet_vblank_irq = 0;
}
