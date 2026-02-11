mic_dma_reg_seq_show(struct seq_file *s, void *pos)
{
	struct mic_dma_device *mic_dma_dev = s->private;
	int i, chan_num, first_chan = mic_dma_dev->start_ch;
	struct mic_dma_chan *ch;

	seq_printf(s, "SBOX_DCR: %#x\n",
		   mic_dma_mmio_read(&mic_dma_dev->mic_ch[first_chan],
				     MIC_DMA_SBOX_BASE + MIC_DMA_SBOX_DCR));
	seq_puts(s, "DMA Channel Registers\n");
	seq_printf(s, "%-10s| %-10s %-10s %-10s %-10s %-10s",
		   "Channel", "DCAR", "DTPR", "DHPR", "DRAR_HI", "DRAR_LO");
	seq_printf(s, " %-11s %-14s %-10s\n", "DCHERR", "DCHERRMSK", "DSTAT");
	for (i = first_chan; i < first_chan + MIC_DMA_NUM_CHAN; i++) {
		ch = &mic_dma_dev->mic_ch[i];
		chan_num = ch->ch_num;
		seq_printf(s, "%-10i| %-#10x %-#10x %-#10x %-#10x",
			   chan_num,
			   mic_dma_read_reg(ch, MIC_DMA_REG_DCAR),
			   mic_dma_read_reg(ch, MIC_DMA_REG_DTPR),
			   mic_dma_read_reg(ch, MIC_DMA_REG_DHPR),
			   mic_dma_read_reg(ch, MIC_DMA_REG_DRAR_HI));
		seq_printf(s, " %-#10x %-#10x %-#14x %-#10x\n",
			   mic_dma_read_reg(ch, MIC_DMA_REG_DRAR_LO),
			   mic_dma_read_reg(ch, MIC_DMA_REG_DCHERR),
			   mic_dma_read_reg(ch, MIC_DMA_REG_DCHERRMSK),
			   mic_dma_read_reg(ch, MIC_DMA_REG_DSTAT));
	}
	return 0;
}
