uda1380_pcm_shutdown(struct snd_pcm_substream *substream,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	u16 clk = uda1380_read_reg_cache(codec, UDA1380_CLK);


	if (clk & R00_DAC_CLK) {
		u16 pm = uda1380_read_reg_cache(codec, UDA1380_PM);
		uda1380_write(codec, UDA1380_PM, ~R02_PON_PLL & pm);
	}

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		clk &= ~(R00_EN_DAC | R00_EN_INT);
	else
		clk &= ~(R00_EN_ADC | R00_EN_DEC);

	uda1380_write(codec, UDA1380_CLK, clk);
}
