sti_uniperiph_dai_create_ctrl(struct snd_soc_dai *dai)
{
	struct sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	struct uniperif *uni = priv->dai_data.uni;
	struct snd_kcontrol_new *ctrl;
	int i;

	if (!uni->num_ctrls)
		return 0;

	for (i = 0; i < uni->num_ctrls; i++) {


		ctrl = &uni->snd_ctrls[i];
		ctrl->index = uni->info->id;
		ctrl->device = uni->info->id;
	}

	return snd_soc_add_dai_controls(dai, uni->snd_ctrls, uni->num_ctrls);
}
