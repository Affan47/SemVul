ssm2602_codec_probe(struct snd_soc_codec *codec)
{
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(codec);
	struct ssm2602_priv *ssm2602 = snd_soc_codec_get_drvdata(codec);
	int ret;

	regmap_update_bits(ssm2602->regmap, SSM2602_LOUT1V,
			    LOUT1V_LRHP_BOTH, LOUT1V_LRHP_BOTH);
	regmap_update_bits(ssm2602->regmap, SSM2602_ROUT1V,
			    ROUT1V_RLHP_BOTH, ROUT1V_RLHP_BOTH);

	ret = snd_soc_add_codec_controls(codec, ssm2602_snd_controls,
			ARRAY_SIZE(ssm2602_snd_controls));
	if (ret)
		return ret;

	ret = snd_soc_dapm_new_controls(dapm, ssm2602_dapm_widgets,
			ARRAY_SIZE(ssm2602_dapm_widgets));
	if (ret)
		return ret;

	return snd_soc_dapm_add_routes(dapm, ssm2602_routes,
			ARRAY_SIZE(ssm2602_routes));
}
