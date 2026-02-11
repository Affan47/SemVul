pcxhr_open(struct snd_pcm_substream *subs)
{
	struct snd_pcxhr       *chip = snd_pcm_substream_chip(subs);
	struct pcxhr_mgr       *mgr = chip->mgr;
	struct snd_pcm_runtime *runtime = subs->runtime;
	struct pcxhr_stream    *stream;
	int err;

	mutex_lock(&mgr->setup_mutex);


	runtime->hw = pcxhr_caps;

	if( subs->stream == SNDRV_PCM_STREAM_PLAYBACK ) {
		dev_dbg(chip->card->dev, "pcxhr_open playback chip%d subs%d\n",
			    chip->chip_idx, subs->number);
		stream = &chip->playback_stream[subs->number];
	} else {
		dev_dbg(chip->card->dev, "pcxhr_open capture chip%d subs%d\n",
			    chip->chip_idx, subs->number);
		if (mgr->mono_capture)
			runtime->hw.channels_max = 1;
		else
			runtime->hw.channels_min = 2;
		stream = &chip->capture_stream[subs->number];
	}
	if (stream->status != PCXHR_STREAM_STATUS_FREE){

		dev_err(chip->card->dev, "pcxhr_open chip%d subs%d in use\n",
			   chip->chip_idx, subs->number);
		mutex_unlock(&mgr->setup_mutex);
		return -EBUSY;
	}


	if (mgr->is_hr_stereo)
		runtime->hw.formats &= ~SNDRV_PCM_FMTBIT_FLOAT_LE;


	err = snd_pcm_hw_constraint_integer(runtime,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	if (err < 0) {
		mutex_unlock(&mgr->setup_mutex);
		return err;
	}


	if (mgr->sample_rate)
		runtime->hw.rate_min = runtime->hw.rate_max = mgr->sample_rate;
	else {
		if (mgr->use_clock_type != PCXHR_CLOCK_TYPE_INTERNAL) {
			int external_rate;
			if (pcxhr_get_external_clock(mgr, mgr->use_clock_type,
						     &external_rate) ||
			    external_rate == 0) {

				mutex_unlock(&mgr->setup_mutex);
				return -EBUSY;
			}
			runtime->hw.rate_min = external_rate;
			runtime->hw.rate_max = external_rate;
		}
	}

	stream->status      = PCXHR_STREAM_STATUS_OPEN;
	stream->substream   = subs;
	stream->channels    = 0;

	runtime->private_data = stream;


	snd_pcm_hw_constraint_step(runtime, 0,
				   SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 32);
	snd_pcm_hw_constraint_step(runtime, 0,
				   SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 32);
	snd_pcm_set_sync(subs);

	mgr->ref_count_rate++;

	mutex_unlock(&mgr->setup_mutex);
	return 0;
}
