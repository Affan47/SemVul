wm8350_set_clkdiv(struct snd_soc_dai *codec_dai, int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 val;

	switch (div_id) {
	case WM8350_ADC_CLKDIV:
		val = snd_soc_read(codec, WM8350_ADC_DIVIDER) &
		    ~WM8350_ADC_CLKDIV_MASK;
		snd_soc_write(codec, WM8350_ADC_DIVIDER, val | div);
		break;
	case WM8350_DAC_CLKDIV:
		val = snd_soc_read(codec, WM8350_DAC_CLOCK_CONTROL) &
		    ~WM8350_DAC_CLKDIV_MASK;
		snd_soc_write(codec, WM8350_DAC_CLOCK_CONTROL, val | div);
		break;
	case WM8350_BCLK_CLKDIV:
		val = snd_soc_read(codec, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_BCLK_DIV_MASK;
		snd_soc_write(codec, WM8350_CLOCK_CONTROL_1, val | div);
		break;
	case WM8350_OPCLK_CLKDIV:
		val = snd_soc_read(codec, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_OPCLK_DIV_MASK;
		snd_soc_write(codec, WM8350_CLOCK_CONTROL_1, val | div);
		break;
	case WM8350_SYS_CLKDIV:
		val = snd_soc_read(codec, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_MCLK_DIV_MASK;
		snd_soc_write(codec, WM8350_CLOCK_CONTROL_1, val | div);
		break;
	case WM8350_DACLR_CLKDIV:
		val = snd_soc_read(codec, WM8350_DAC_LR_RATE) &
		    ~WM8350_DACLRC_RATE_MASK;
		snd_soc_write(codec, WM8350_DAC_LR_RATE, val | div);
		break;
	case WM8350_ADCLR_CLKDIV:
		val = snd_soc_read(codec, WM8350_ADC_LR_RATE) &
		    ~WM8350_ADCLRC_RATE_MASK;
		snd_soc_write(codec, WM8350_ADC_LR_RATE, val | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
