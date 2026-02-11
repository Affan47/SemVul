vdp_dma_copy(void)
{
	int length = segac2_vdp_regs[19] | (segac2_vdp_regs[20] << 8);
	int source = segac2_vdp_regs[21] | (segac2_vdp_regs[22] << 8);
	int count;


	if (!length)
		length = 0xffff;


	for (count = 0; count < length; count++)
	{
		VDP_VRAM_BYTE(vdp_address) = VDP_VRAM_BYTE(source++);
		vdp_address += segac2_vdp_regs[15];
	}
}
