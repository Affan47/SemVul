snd_fm801_capture_trigger(struct snd_pcm_substream *substream,
				     int cmd)
{
	struct fm801 *chip = snd_pcm_substream_chip(substream);

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		chip->cap_ctrl &= ~(FM801_BUF1_LAST |
				     FM801_BUF2_LAST |
				     FM801_PAUSE);
		chip->cap_ctrl |= FM801_START |
				   FM801_IMMED_STOP;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		chip->cap_ctrl &= ~(FM801_START | FM801_PAUSE);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		chip->cap_ctrl |= FM801_PAUSE;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		chip->cap_ctrl &= ~FM801_PAUSE;
		break;
	default:
		spin_unlock(&chip->reg_lock);
		snd_BUG();
		return -EINVAL;
	}
	fm801_writew(chip, CAP_CTRL, chip->cap_ctrl);
	spin_unlock(&chip->reg_lock);
	return 0;
}
