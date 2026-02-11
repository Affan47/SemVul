snd_korg1212_hw_params(struct snd_pcm_substream *substream,
                             struct snd_pcm_hw_params *params)
{
        unsigned long flags;
        struct snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
        int err;
	pid_t this_pid;
	pid_t other_pid;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_hw_params [%s]\n",
			   stateName[korg1212->cardState]);

        spin_lock_irqsave(&korg1212->lock, flags);

	if (substream->pstr->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		this_pid = korg1212->playback_pid;
		other_pid = korg1212->capture_pid;
	} else {
		this_pid = korg1212->capture_pid;
		other_pid = korg1212->playback_pid;
	}

	if ((other_pid > 0) && (this_pid != other_pid)) {


		if ((int)params_rate(params) != korg1212->clkRate) {
			spin_unlock_irqrestore(&korg1212->lock, flags);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			return -EBUSY;
		}

        	spin_unlock_irqrestore(&korg1212->lock, flags);
	        return 0;
	}

        if ((err = snd_korg1212_SetRate(korg1212, params_rate(params))) < 0) {
                spin_unlock_irqrestore(&korg1212->lock, flags);
                return err;
        }

	korg1212->channels = params_channels(params);
        korg1212->periodsize = K1212_PERIOD_BYTES;

        spin_unlock_irqrestore(&korg1212->lock, flags);

        return 0;
}
