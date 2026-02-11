dac33_read(struct snd_soc_codec *codec, unsigned int reg,
		      u8 *value)
{
	struct tlv320dac33_priv *dac33 = snd_soc_codec_get_drvdata(codec);
	int val, ret = 0;

	*value = reg & 0xff;


	if (dac33->chip_power) {
		val = i2c_smbus_read_byte_data(codec->control_data, value[0]);
		if (val < 0) {
			dev_err(codec->dev, "Read failed (%d)\n", val);
			value[0] = dac33_read_reg_cache(codec, reg);
			ret = val;
		} else {
			value[0] = val;
			dac33_write_reg_cache(codec, reg, val);
		}
	} else {
		value[0] = dac33_read_reg_cache(codec, reg);
	}

	return ret;
}
