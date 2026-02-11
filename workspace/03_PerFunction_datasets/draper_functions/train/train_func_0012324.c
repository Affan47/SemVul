stop_stream(struct snd_dice *dice, struct amdtp_stream *stream)
{
	amdtp_stream_pcm_abort(stream);
	amdtp_stream_stop(stream);

	if (stream == &dice->tx_stream)
		release_resources(dice, &dice->tx_resources);
	else
		release_resources(dice, &dice->rx_resources);
}
