pcxhr_prepare(struct snd_pcm_substream *subs)
{
	struct snd_pcxhr *chip = snd_pcm_substream_chip(subs);
	struct pcxhr_mgr *mgr = chip->mgr;
	int err = 0;

	dev_dbg(chip->card->dev,
		"pcxhr_prepare : period_size(%lx) periods(%x) buffer_size(%lx)\n",
		    subs->runtime->period_size, subs->runtime->periods,
		    subs->runtime->buffer_size);

	mutex_lock(&mgr->setup_mutex);

	do {


		if (mgr->sample_rate != subs->runtime->rate) {
			err = pcxhr_set_clock(mgr, subs->runtime->rate);
			if (err)
				break;
			if (mgr->sample_rate == 0)

				err = pcxhr_hardware_timer(mgr, 1);
			mgr->sample_rate = subs->runtime->rate;
		}
	} while(0);

	mutex_unlock(&mgr->setup_mutex);

	return err;
}
