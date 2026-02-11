adau1701_reset(struct snd_soc_codec *codec, unsigned int clkdiv,
	unsigned int rate)
{
	struct adau1701 *adau1701 = snd_soc_codec_get_drvdata(codec);
	int ret;

	sigmadsp_reset(adau1701->sigmadsp);

	if (clkdiv != ADAU1707_CLKDIV_UNSET &&
	    gpio_is_valid(adau1701->gpio_pll_mode[0]) &&
	    gpio_is_valid(adau1701->gpio_pll_mode[1])) {
		switch (clkdiv) {
		case 64:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 0);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 0);
			break;
		case 256:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 0);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 1);
			break;
		case 384:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 1);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 0);
			break;
		case 0:
		case 512:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 1);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 1);
			break;
		}
	}

	adau1701->pll_clkdiv = clkdiv;

	if (gpio_is_valid(adau1701->gpio_nreset)) {
		gpio_set_value_cansleep(adau1701->gpio_nreset, 0);

		udelay(1);
		gpio_set_value_cansleep(adau1701->gpio_nreset, 1);

		mdelay(85);
	}


	if (clkdiv != ADAU1707_CLKDIV_UNSET) {
		ret = sigmadsp_setup(adau1701->sigmadsp, rate);
		if (ret) {
			dev_warn(codec->dev, "Failed to load firmware\n");
			return ret;
		}
	}

	regmap_write(adau1701->regmap, ADAU1701_DACSET, ADAU1701_DACSET_DACINIT);
	regmap_write(adau1701->regmap, ADAU1701_DSPCTRL, ADAU1701_DSPCTRL_CR);

	regcache_mark_dirty(adau1701->regmap);
	regcache_sync(adau1701->regmap);

	return 0;
}
