snd_azf3328_pcm_interrupt(struct snd_azf3328 *chip,
			  const struct snd_azf3328_codec_data *first_codec,
			  u8 status
)
{
	u8 which;
	enum snd_azf3328_codec_type codec_type;
	const struct snd_azf3328_codec_data *codec = first_codec;

	for (codec_type = AZF_CODEC_PLAYBACK;
		 codec_type <= AZF_CODEC_I2S_OUT;
			 ++codec_type, ++codec) {


		if (!(status & (1 << codec_type)))
			continue;

		spin_lock(codec->lock);
		which = snd_azf3328_codec_inb(codec, IDX_IO_CODEC_IRQTYPE);

		snd_azf3328_codec_outb(codec, IDX_IO_CODEC_IRQTYPE, which);
		spin_unlock(codec->lock);

		if (codec->substream) {
			snd_pcm_period_elapsed(codec->substream);
			dev_dbg(chip->card->dev, "%s period done (#%x), @ %x\n",
				codec->name,
				which,
				snd_azf3328_codec_inl(
					codec, IDX_IO_CODEC_DMA_CURRPOS));
		} else
			dev_warn(chip->card->dev, "irq handler problem!\n");
		if (which & IRQ_SOMETHING)
			snd_azf3328_irq_log_unknown_type(chip, which);
	}
}
