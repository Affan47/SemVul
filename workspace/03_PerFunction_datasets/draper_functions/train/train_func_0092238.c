sti_uniperiph_dai_resume(struct snd_soc_dai *dai)
{
	struct sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	struct uniperif *uni = priv->dai_data.uni;
	int ret;

	if (of_device_is_compatible(dai->dev->of_node, "st,sti-uni-player")) {
		ret = uni_player_resume(uni);
		if (ret)
			return ret;
	}


	ret = pinctrl_pm_select_default_state(uni->dev);
	if (ret)
		dev_err(uni->dev, "%s: failed to select pinctrl state",
			__func__);

	return ret;
}
