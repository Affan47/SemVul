skl_coupled_trigger(struct snd_pcm_substream *substream,
					int cmd)
{
	struct hdac_ext_bus *ebus = get_bus_ctx(substream);
	struct hdac_bus *bus = ebus_to_hbus(ebus);
	struct hdac_ext_stream *stream;
	struct snd_pcm_substream *s;
	bool start;
	int sbits = 0;
	unsigned long cookie;
	struct hdac_stream *hstr;

	stream = get_hdac_ext_stream(substream);
	hstr = hdac_stream(stream);

	dev_dbg(bus->dev, "In %s cmd=%d\n", __func__, cmd);

	if (!hstr->prepared)
		return -EPIPE;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		start = true;
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
		start = false;
		break;

	default:
		return -EINVAL;
	}

	snd_pcm_group_for_each_entry(s, substream) {
		if (s->pcm->card != substream->pcm->card)
			continue;
		stream = get_hdac_ext_stream(s);
		sbits |= 1 << hdac_stream(stream)->index;
		snd_pcm_trigger_done(s, substream);
	}

	spin_lock_irqsave(&bus->reg_lock, cookie);


	snd_hdac_stream_sync_trigger(hstr, true, sbits, AZX_REG_SSYNC);

	snd_pcm_group_for_each_entry(s, substream) {
		if (s->pcm->card != substream->pcm->card)
			continue;
		stream = get_hdac_ext_stream(s);
		if (start)
			snd_hdac_stream_start(hdac_stream(stream), true);
		else
			snd_hdac_stream_stop(hdac_stream(stream));
	}
	spin_unlock_irqrestore(&bus->reg_lock, cookie);

	snd_hdac_stream_sync(hstr, start, sbits);

	spin_lock_irqsave(&bus->reg_lock, cookie);


	snd_hdac_stream_sync_trigger(hstr, false, sbits, AZX_REG_SSYNC);
	if (start)
		snd_hdac_stream_timecounter_init(hstr, sbits);
	spin_unlock_irqrestore(&bus->reg_lock, cookie);

	return 0;
}
