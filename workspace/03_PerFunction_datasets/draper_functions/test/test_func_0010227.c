ess_audio_output_block_audio2
	(int dev, unsigned long buf, int nr_bytes, int intrflag)
{
	int count = nr_bytes;
	sb_devc *devc = audio_devs[dev]->devc;
	short c = -nr_bytes;

	if (audio_devs[dev]->dmap_out->dma > 3) count >>= 1;
	count--;

	ess_setmixer (devc, 0x74, (unsigned char) ((unsigned short) c & 0xff));
	ess_setmixer (devc, 0x76, (unsigned char) (((unsigned short) c >> 8) & 0xff));
	ess_chgmixer (devc, 0x78, 0x03, 0x03);

	devc->irq_mode_16 = IMODE_OUTPUT;
	devc->intr_active_16 = 1;
}
