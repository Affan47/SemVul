pcm_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_dg00x *dg00x = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	mutex_lock(&dg00x->mutex);

	err = snd_dg00x_stream_start_duplex(dg00x, runtime->rate);
	if (err >= 0)
		amdtp_stream_pcm_prepare(&dg00x->tx_stream);

	mutex_unlock(&dg00x->mutex);

	return err;
}
