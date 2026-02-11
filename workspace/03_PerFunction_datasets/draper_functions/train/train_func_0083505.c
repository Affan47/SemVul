cyber_enable_fullscreen_alpha(int enable)
{
	cyber_grphw(0xfa, 0);

	cyber_out8(cyber_mmio, SEQINDEX, 0x4b);
	if (enable)
		cyber_out8(cyber_mmio, SEQDATA, (cyber_in8(cyber_mmio, SEQDATA) | 0x40));
     else
		cyber_out8(cyber_mmio, SEQDATA, (cyber_in8(cyber_mmio, SEQDATA) & 0xBF));
}
