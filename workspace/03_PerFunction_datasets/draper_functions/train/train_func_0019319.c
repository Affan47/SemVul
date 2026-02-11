wm8991_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
				 int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg;

	switch (div_id) {
	case WM8991_MCLK_DIV:
		reg = snd_soc_read(codec, WM8991_CLOCKING_2) &
		      ~WM8991_MCLK_DIV_MASK;
		snd_soc_write(codec, WM8991_CLOCKING_2, reg | div);
		break;
	case WM8991_DACCLK_DIV:
		reg = snd_soc_read(codec, WM8991_CLOCKING_2) &
		      ~WM8991_DAC_CLKDIV_MASK;
		snd_soc_write(codec, WM8991_CLOCKING_2, reg | div);
		break;
	case WM8991_ADCCLK_DIV:
		reg = snd_soc_read(codec, WM8991_CLOCKING_2) &
		      ~WM8991_ADC_CLKDIV_MASK;
		snd_soc_write(codec, WM8991_CLOCKING_2, reg | div);
		break;
	case WM8991_BCLK_DIV:
		reg = snd_soc_read(codec, WM8991_CLOCKING_1) &
		      ~WM8991_BCLK_DIV_MASK;
		snd_soc_write(codec, WM8991_CLOCKING_1, reg | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
