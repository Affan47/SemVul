da9055_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
			      int source, unsigned int fref, unsigned int fout)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct da9055_priv *da9055 = snd_soc_codec_get_drvdata(codec);

	u8 pll_frac_top, pll_frac_bot, pll_integer, cnt;


	snd_soc_update_bits(codec, DA9055_PLL_CTRL, DA9055_PLL_EN, 0);


	if (!da9055->master && (fout != 2822400))
		goto pll_err;


	for (cnt = 0; cnt < ARRAY_SIZE(da9055_pll_div); cnt++) {

		if ((fref == da9055_pll_div[cnt].fref) &&
		    (da9055->master ==  da9055_pll_div[cnt].mode) &&
		    (fout == da9055_pll_div[cnt].fout)) {

			pll_frac_top = da9055_pll_div[cnt].frac_top;
			pll_frac_bot = da9055_pll_div[cnt].frac_bot;
			pll_integer = da9055_pll_div[cnt].integer;
			break;
		}
	}
	if (cnt >= ARRAY_SIZE(da9055_pll_div))
		goto pll_err;


	snd_soc_write(codec, DA9055_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_write(codec, DA9055_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_write(codec, DA9055_PLL_INTEGER, pll_integer);

	return 0;
pll_err:
	dev_err(codec_dai->dev, "Error in setting up PLL\n");
	return -EINVAL;
}
