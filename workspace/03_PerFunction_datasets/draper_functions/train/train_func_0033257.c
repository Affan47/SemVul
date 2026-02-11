cx88_start_audio_dma(struct cx88_core *core)
{

	int bpl = cx88_sram_channels[SRAM_CH25].fifo_size/4;

	int rds_bpl = cx88_sram_channels[SRAM_CH27].fifo_size/AUD_RDS_LINES;


	if (cx_read(MO_AUD_DMACNTRL) & 0x10)
		return 0;


	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH25], bpl, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH26], bpl, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH27],
				rds_bpl, 0);

	cx_write(MO_AUDD_LNGTH, bpl);
	cx_write(MO_AUDR_LNGTH, rds_bpl);


	cx_write(MO_AUD_DMACNTRL, 0x0007);

	return 0;
}
