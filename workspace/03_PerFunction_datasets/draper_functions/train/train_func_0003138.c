rk_spdif_trigger(struct snd_pcm_substream *substream,
				int cmd, struct snd_soc_dai *dai)
{
	struct rk_spdif_dev *spdif = snd_soc_dai_get_drvdata(dai);
	int ret;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = regmap_update_bits(spdif->regmap, SPDIF_DMACR,
				   SPDIF_DMACR_TDE_ENABLE |
				   SPDIF_DMACR_TDL_MASK,
				   SPDIF_DMACR_TDE_ENABLE |
				   SPDIF_DMACR_TDL(16));

		if (ret != 0)
			return ret;

		ret = regmap_update_bits(spdif->regmap, SPDIF_XFER,
				   SPDIF_XFER_TXS_START,
				   SPDIF_XFER_TXS_START);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = regmap_update_bits(spdif->regmap, SPDIF_DMACR,
				   SPDIF_DMACR_TDE_ENABLE,
				   SPDIF_DMACR_TDE_DISABLE);

		if (ret != 0)
			return ret;

		ret = regmap_update_bits(spdif->regmap, SPDIF_XFER,
				   SPDIF_XFER_TXS_START,
				   SPDIF_XFER_TXS_STOP);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
