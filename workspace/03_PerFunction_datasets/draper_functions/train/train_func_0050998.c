snd_atiixp_spdif_prepare(struct snd_pcm_substream *substream)
{
	struct atiixp *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	if (chip->spdif_over_aclink) {
		unsigned int data;

		atiixp_update(chip, CMD, ATI_REG_CMD_SPDF_CONFIG_MASK,
			      ATI_REG_CMD_SPDF_CONFIG_01);
		data = atiixp_read(chip, OUT_DMA_SLOT) & ~ATI_REG_OUT_DMA_SLOT_MASK;
		data |= ATI_REG_OUT_DMA_SLOT_BIT(10) |
			ATI_REG_OUT_DMA_SLOT_BIT(11);
		data |= 0x04 << ATI_REG_OUT_DMA_THRESHOLD_SHIFT;
		atiixp_write(chip, OUT_DMA_SLOT, data);
		atiixp_update(chip, CMD, ATI_REG_CMD_INTERLEAVE_OUT,
			      substream->runtime->format == SNDRV_PCM_FORMAT_S16_LE ?
			      ATI_REG_CMD_INTERLEAVE_OUT : 0);
	} else {
		atiixp_update(chip, CMD, ATI_REG_CMD_SPDF_CONFIG_MASK, 0);
		atiixp_update(chip, CMD, ATI_REG_CMD_INTERLEAVE_SPDF, 0);
	}
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}
