axi_spdif_trigger(struct snd_pcm_substream *substream, int cmd,
	struct snd_soc_dai *dai)
{
	struct axi_spdif *spdif = snd_soc_dai_get_drvdata(dai);
	unsigned int val;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = AXI_SPDIF_CTRL_TXDATA;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = 0;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(spdif->regmap, AXI_SPDIF_REG_CTRL,
		AXI_SPDIF_CTRL_TXDATA, val);

	return 0;
}
