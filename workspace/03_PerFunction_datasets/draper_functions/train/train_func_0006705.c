da7210_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
			      int source, unsigned int fref, unsigned int fout)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct da7210_priv *da7210 = snd_soc_codec_get_drvdata(codec);

	u8 pll_div1, pll_div2, pll_div3, cnt;


	if (!da7210->master)
		fout = 2822400;


	for (cnt = 0; cnt < ARRAY_SIZE(da7210_pll_div); cnt++) {

		if ((fref == da7210_pll_div[cnt].fref) &&
		    (da7210->master ==  da7210_pll_div[cnt].mode) &&
		    (fout == da7210_pll_div[cnt].fout)) {

			pll_div1 = da7210_pll_div[cnt].div1;
			pll_div2 = da7210_pll_div[cnt].div2;
			pll_div3 = da7210_pll_div[cnt].div3;
			break;
		}
	}
	if (cnt >= ARRAY_SIZE(da7210_pll_div))
		goto err;


	snd_soc_update_bits(codec, DA7210_STARTUP1, DA7210_SC_MST_EN, 0);

	snd_soc_write(codec, DA7210_PLL_DIV1, pll_div1);
	snd_soc_write(codec, DA7210_PLL_DIV2, pll_div2);
	snd_soc_update_bits(codec, DA7210_PLL_DIV3,
				   DA7210_PLL_DIV_L_MASK, pll_div3);


	snd_soc_update_bits(codec, DA7210_PLL, DA7210_PLL_EN, DA7210_PLL_EN);


	snd_soc_update_bits(codec, DA7210_STARTUP1, DA7210_SC_MST_EN,
						    DA7210_SC_MST_EN);
	return 0;
err:
	dev_err(codec_dai->dev, "Unsupported PLL input frequency %d\n", fref);
	return -EINVAL;
}
