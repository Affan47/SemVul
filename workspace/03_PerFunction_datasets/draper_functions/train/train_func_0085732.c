snd_pcm_post_stop(struct snd_pcm_substream *substream, int state)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (runtime->status->state != state) {
		snd_pcm_trigger_tstamp(substream);
		runtime->status->state = state;
		snd_pcm_timer_notify(substream, SNDRV_TIMER_EVENT_MSTOP);
	}
	wake_up(&runtime->sleep);
	wake_up(&runtime->tsleep);
}
