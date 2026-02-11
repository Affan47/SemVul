snd_pcm_prepare(struct snd_pcm_substream *substream,
			   struct file *file)
{
	int res;
	struct snd_card *card = substream->pcm->card;
	int f_flags;

	if (file)
		f_flags = file->f_flags;
	else
		f_flags = substream->f_flags;

	snd_power_lock(card);
	if ((res = snd_power_wait(card, SNDRV_CTL_POWER_D0)) >= 0)
		res = snd_pcm_action_nonatomic(&snd_pcm_action_prepare,
					       substream, f_flags);
	snd_power_unlock(card);
	return res;
}
