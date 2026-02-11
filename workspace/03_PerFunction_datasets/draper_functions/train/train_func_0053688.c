snd_p16v_pcm_open_playback_channel(struct snd_pcm_substream *substream, int channel_id)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
        struct snd_emu10k1_voice *channel = &(emu->p16v_voices[channel_id]);
	struct snd_emu10k1_pcm *epcm;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);


	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = emu;
	epcm->substream = substream;


	runtime->private_data = epcm;
	runtime->private_free = snd_p16v_pcm_free_substream;

	runtime->hw = snd_p16v_playback_hw;

        channel->emu = emu;
        channel->number = channel_id;

        channel->use=1;
#if 0
	dev_dbg(emu->card->dev,
		   "p16v: open channel_id=%d, channel=%p, use=0x%x\n",
		   channel_id, channel, channel->use);
	dev_dbg(emu->card->dev, "open:channel_id=%d, chip=%p, channel=%p\n",
	       channel_id, chip, channel);
#endif

	channel->epcm = epcm;
	if ((err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
                return err;

	runtime->sync.id32[0] = substream->pcm->card->number;
	runtime->sync.id32[1] = 'P';
	runtime->sync.id32[2] = 16;
	runtime->sync.id32[3] = 'V';

	return 0;
}
