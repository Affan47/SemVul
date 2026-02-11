headset_ramp(struct snd_soc_codec *codec, int ramp)
{
	unsigned char hs_gain, hs_pop;
	struct twl4030_priv *twl4030 = snd_soc_codec_get_drvdata(codec);
	struct twl4030_codec_data *pdata = twl4030->pdata;

	unsigned int ramp_base[] = {524288, 1048576, 2097152, 4194304,
				    8388608, 16777216, 33554432, 67108864};
	unsigned int delay;

	hs_gain = twl4030_read(codec, TWL4030_REG_HS_GAIN_SET);
	hs_pop = twl4030_read(codec, TWL4030_REG_HS_POPN_SET);
	delay = (ramp_base[(hs_pop & TWL4030_RAMP_DELAY) >> 2] /
		twl4030->sysclk) + 1;


	if (pdata && pdata->hs_extmute) {
		if (gpio_is_valid(pdata->hs_extmute_gpio)) {
			gpio_set_value(pdata->hs_extmute_gpio, 1);
		} else {
			hs_pop |= TWL4030_EXTMUTE;
			twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
		}
	}

	if (ramp) {

		hs_pop |= TWL4030_VMID_EN;
		twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);

		twl_i2c_write_u8(TWL4030_MODULE_AUDIO_VOICE, hs_gain,
				 TWL4030_REG_HS_GAIN_SET);
		hs_pop |= TWL4030_RAMP_EN;
		twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);

		twl4030_wait_ms(delay);
	} else {


		hs_pop &= ~TWL4030_RAMP_EN;
		twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);

		twl4030_wait_ms(delay);

		twl_i2c_write_u8(TWL4030_MODULE_AUDIO_VOICE, hs_gain & (~0x0f),
				 TWL4030_REG_HS_GAIN_SET);

		hs_pop &= ~TWL4030_VMID_EN;
		twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
	}


	if (pdata && pdata->hs_extmute) {
		if (gpio_is_valid(pdata->hs_extmute_gpio)) {
			gpio_set_value(pdata->hs_extmute_gpio, 0);
		} else {
			hs_pop &= ~TWL4030_EXTMUTE;
			twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
		}
	}
}
