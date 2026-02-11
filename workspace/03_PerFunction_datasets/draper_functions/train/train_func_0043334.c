snd_rme32_playback_adat_open(struct snd_pcm_substream *substream)
{
	int rate, dummy;
	struct rme32 *rme32 = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	snd_pcm_set_sync(substream);

	spin_lock_irq(&rme32->lock);
        if (rme32->playback_substream != NULL) {
		spin_unlock_irq(&rme32->lock);
                return -EBUSY;
        }
	rme32->wcreg |= RME32_WCR_ADAT;
	writel(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	rme32->playback_substream = substream;
	spin_unlock_irq(&rme32->lock);

	if (rme32->fullduplex_mode)
		runtime->hw = snd_rme32_adat_fd_info;
	else
		runtime->hw = snd_rme32_adat_info;
	if ((rme32->rcreg & RME32_RCR_KMODE) &&
	    (rate = snd_rme32_capture_getrate(rme32, &dummy)) > 0) {

                runtime->hw.rates = snd_pcm_rate_to_rate_bit(rate);
                runtime->hw.rate_min = rate;
                runtime->hw.rate_max = rate;
	}

	snd_rme32_set_buffer_constraint(rme32, runtime);
	return 0;
}
