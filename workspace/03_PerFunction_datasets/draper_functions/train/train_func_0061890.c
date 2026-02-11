_dsp_clear_sample_buffer (struct snd_cs46xx *chip, u32 sample_buffer_addr,
				      int dword_count)
{
	void __iomem *dst = chip->region.idx[2].remap_addr + sample_buffer_addr;
	int i;

	for (i = 0; i < dword_count ; ++i ) {
		writel(0, dst);
		dst += 4;
	}
}
