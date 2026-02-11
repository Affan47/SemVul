snd_emu10k1x_pcm_trigger_capture(struct snd_pcm_substream *substream,
					    int cmd)
{
	struct emu10k1x *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct emu10k1x_pcm *epcm = runtime->private_data;
	int result = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_emu10k1x_intr_enable(emu, INTE_CAP_0_LOOP |
					 INTE_CAP_0_HALF_LOOP);
		snd_emu10k1x_ptr_write(emu, TRIGGER_CHANNEL, 0, snd_emu10k1x_ptr_read(emu, TRIGGER_CHANNEL, 0)|TRIGGER_CAPTURE);
		epcm->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		epcm->running = 0;
		snd_emu10k1x_intr_disable(emu, INTE_CAP_0_LOOP |
					  INTE_CAP_0_HALF_LOOP);
		snd_emu10k1x_ptr_write(emu, TRIGGER_CHANNEL, 0, snd_emu10k1x_ptr_read(emu, TRIGGER_CHANNEL, 0) & ~(TRIGGER_CAPTURE));
		break;
	default:
		result = -EINVAL;
		break;
	}
	return result;
}
