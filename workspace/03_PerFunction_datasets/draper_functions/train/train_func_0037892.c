dac33_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct tlv320dac33_priv *dac33 = snd_soc_codec_get_drvdata(codec);
	u8 ioc_reg, asrcb_reg;

	ioc_reg = dac33_read_reg_cache(codec, DAC33_INT_OSC_CTRL);
	asrcb_reg = dac33_read_reg_cache(codec, DAC33_ASRC_CTRL_B);
	switch (clk_id) {
	case TLV320DAC33_MCLK:
		ioc_reg |= DAC33_REFSEL;
		asrcb_reg |= DAC33_SRCREFSEL;
		break;
	case TLV320DAC33_SLEEPCLK:
		ioc_reg &= ~DAC33_REFSEL;
		asrcb_reg &= ~DAC33_SRCREFSEL;
		break;
	default:
		dev_err(codec->dev, "Invalid clock ID (%d)\n", clk_id);
		break;
	}
	dac33->refclk = freq;

	dac33_write_reg_cache(codec, DAC33_INT_OSC_CTRL, ioc_reg);
	dac33_write_reg_cache(codec, DAC33_ASRC_CTRL_B, asrcb_reg);

	return 0;
}
