fsl_spdif_qget(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct fsl_spdif_priv *spdif_priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct spdif_mixer_control *ctrl = &spdif_priv->fsl_spdif_control;
	unsigned long flags;
	int ret = -EAGAIN;

	spin_lock_irqsave(&ctrl->ctl_lock, flags);
	if (ctrl->ready_buf) {
		int idx = (ctrl->ready_buf - 1) * SPDIF_QSUB_SIZE;
		memcpy(&ucontrol->value.bytes.data[0],
				&ctrl->qsub[idx], SPDIF_QSUB_SIZE);
		ret = 0;
	}
	spin_unlock_irqrestore(&ctrl->ctl_lock, flags);

	return ret;
}
