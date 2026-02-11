snd_solo_pcm_trigger(struct snd_pcm_substream *ss, int cmd)
{
	struct solo_snd_pcm *solo_pcm = snd_pcm_substream_chip(ss);
	struct solo_dev *solo_dev = solo_pcm->solo_dev;
	int ret = 0;

	spin_lock(&solo_pcm->lock);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (solo_pcm->on == 0) {

			if (atomic_inc_return(&solo_dev->snd_users) == 1)
				solo_irq_on(solo_dev, SOLO_IRQ_G723);
			solo_pcm->on = 1;
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (solo_pcm->on) {

			if (atomic_dec_return(&solo_dev->snd_users) == 0)
				solo_irq_off(solo_dev, SOLO_IRQ_G723);
			solo_pcm->on = 0;
		}
		break;
	default:
		ret = -EINVAL;
	}

	spin_unlock(&solo_pcm->lock);

	return ret;
}
