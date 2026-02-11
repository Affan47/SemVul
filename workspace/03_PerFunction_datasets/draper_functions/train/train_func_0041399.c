snd_pcm_ioplug_start(snd_pcm_t *pcm)
{
	ioplug_priv_t *io = pcm->private_data;
	int err;

	if (io->data->state != SND_PCM_STATE_PREPARED)
		return -EBADFD;

	err = io->data->callback->start(io->data);
	if (err < 0)
		return err;

	gettimestamp(&io->trigger_tstamp, pcm->monotonic);
	io->data->state = SND_PCM_STATE_RUNNING;

	return 0;
}
