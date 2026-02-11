sst_soc_complete(struct device *dev)
{
	struct sst_data *drv = dev_get_drvdata(dev);
	int i;

	if (!drv->soc_card)
		return;


	for (i = 0; i < drv->soc_card->num_rtd; i++) {
		struct snd_soc_dai *dai = drv->soc_card->rtd[i].cpu_dai;

		if (dai->active) {
			sst_handle_vb_timer(dai, true);
			send_ssp_cmd(dai, dai->name, 1);
		}
	}
	snd_soc_resume(drv->soc_card->dev);
}
