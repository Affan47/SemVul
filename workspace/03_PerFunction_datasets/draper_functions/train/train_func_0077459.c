dac33_write(struct snd_soc_codec *codec, unsigned int reg,
		       unsigned int value)
{
	struct tlv320dac33_priv *dac33 = snd_soc_codec_get_drvdata(codec);
	u8 data[2];
	int ret = 0;


	data[0] = reg & 0xff;
	data[1] = value & 0xff;

	dac33_write_reg_cache(codec, data[0], data[1]);
	if (dac33->chip_power) {
		ret = codec->hw_write(codec->control_data, data, 2);
		if (ret != 2)
			dev_err(codec->dev, "Write failed (%d)\n", ret);
		else
			ret = 0;
	}

	return ret;
}
