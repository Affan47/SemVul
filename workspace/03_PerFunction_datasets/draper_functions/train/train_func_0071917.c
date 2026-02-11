kirkwood_i2s_rec_trigger(struct snd_pcm_substream *substream,
				int cmd, struct snd_soc_dai *dai)
{
	struct kirkwood_dma_data *priv = snd_soc_dai_get_drvdata(dai);
	uint32_t ctl, value;

	value = readl(priv->io + KIRKWOOD_RECCTL);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:

		ctl = priv->ctl_rec;
		if (dai->id == 0)
			ctl &= ~KIRKWOOD_RECCTL_SPDIF_EN;
		else
			ctl &= ~KIRKWOOD_RECCTL_I2S_EN;

		value = ctl & ~KIRKWOOD_RECCTL_ENABLE_MASK;
		writel(value, priv->io + KIRKWOOD_RECCTL);


		value = readl(priv->io + KIRKWOOD_INT_MASK);
		value |= KIRKWOOD_INT_CAUSE_REC_BYTES;
		writel(value, priv->io + KIRKWOOD_INT_MASK);


		writel(ctl, priv->io + KIRKWOOD_RECCTL);
		break;

	case SNDRV_PCM_TRIGGER_STOP:

		value = readl(priv->io + KIRKWOOD_RECCTL);
		value |= KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE;
		writel(value, priv->io + KIRKWOOD_RECCTL);

		value = readl(priv->io + KIRKWOOD_INT_MASK);
		value &= ~KIRKWOOD_INT_CAUSE_REC_BYTES;
		writel(value, priv->io + KIRKWOOD_INT_MASK);


		value = readl(priv->io + KIRKWOOD_RECCTL);
		value &= ~KIRKWOOD_RECCTL_ENABLE_MASK;
		writel(value, priv->io + KIRKWOOD_RECCTL);
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		value = readl(priv->io + KIRKWOOD_RECCTL);
		value |= KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE;
		writel(value, priv->io + KIRKWOOD_RECCTL);
		break;

	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		value = readl(priv->io + KIRKWOOD_RECCTL);
		value &= ~(KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE);
		writel(value, priv->io + KIRKWOOD_RECCTL);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}
