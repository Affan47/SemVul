twl4030_init_chip(struct snd_soc_codec *codec)
{
	struct twl4030_codec_data *pdata;
	struct twl4030_priv *twl4030 = snd_soc_codec_get_drvdata(codec);
	u8 reg, byte;
	int i = 0;

	pdata = twl4030_get_pdata(codec);

	if (pdata && pdata->hs_extmute) {
		if (gpio_is_valid(pdata->hs_extmute_gpio)) {
			int ret;

			if (!pdata->hs_extmute_gpio)
				dev_warn(codec->dev,
					"Extmute GPIO is 0 is this correct?\n");

			ret = gpio_request_one(pdata->hs_extmute_gpio,
					       GPIOF_OUT_INIT_LOW,
					       "hs_extmute");
			if (ret) {
				dev_err(codec->dev,
					"Failed to get hs_extmute GPIO\n");
				pdata->hs_extmute_gpio = -1;
			}
		} else {
			u8 pin_mux;


			twl_i2c_read_u8(TWL4030_MODULE_INTBR, &pin_mux,
					TWL4030_PMBR1_REG);
			pin_mux &= ~TWL4030_GPIO6_PWM0_MUTE(0x03);
			pin_mux |= TWL4030_GPIO6_PWM0_MUTE(0x02);
			twl_i2c_write_u8(TWL4030_MODULE_INTBR, pin_mux,
					 TWL4030_PMBR1_REG);
		}
	}


	tw4030_init_ctl_cache(twl4030);


	reg = twl4030_read(codec, TWL4030_REG_MISC_SET_1);
	twl4030_write(codec, TWL4030_REG_MISC_SET_1,
		      reg | TWL4030_SMOOTH_ANAVOL_EN);

	twl4030_write(codec, TWL4030_REG_OPTION,
		      TWL4030_ATXL1_EN | TWL4030_ATXR1_EN |
		      TWL4030_ARXL2_EN | TWL4030_ARXR2_EN);


	twl4030_write(codec, TWL4030_REG_ARXR2_APGA_CTL, 0x32);


	if (!pdata)
		return;

	twl4030->pdata = pdata;

	reg = twl4030_read(codec, TWL4030_REG_HS_POPN_SET);
	reg &= ~TWL4030_RAMP_DELAY;
	reg |= (pdata->ramp_delay_value << 2);
	twl4030_write(codec, TWL4030_REG_HS_POPN_SET, reg);


	twl4030_codec_enable(codec, 1);

	reg = twl4030_read(codec, TWL4030_REG_ANAMICL);
	reg &= ~TWL4030_OFFSET_CNCL_SEL;
	reg |= pdata->offset_cncl_path;
	twl4030_write(codec, TWL4030_REG_ANAMICL,
		      reg | TWL4030_CNCL_OFFSET_START);


	msleep(20);
	do {
		usleep_range(1000, 2000);
		twl_set_regcache_bypass(TWL4030_MODULE_AUDIO_VOICE, true);
		twl_i2c_read_u8(TWL4030_MODULE_AUDIO_VOICE, &byte,
				TWL4030_REG_ANAMICL);
		twl_set_regcache_bypass(TWL4030_MODULE_AUDIO_VOICE, false);
	} while ((i++ < 100) &&
		 ((byte & TWL4030_CNCL_OFFSET_START) ==
		  TWL4030_CNCL_OFFSET_START));

	twl4030_codec_enable(codec, 0);
}
