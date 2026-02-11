snd_dg00x_stream_start_duplex(struct snd_dg00x *dg00x, unsigned int rate)
{
	unsigned int curr_rate;
	int err = 0;

	if (dg00x->substreams_counter == 0)
		goto end;


	err = snd_dg00x_stream_get_local_rate(dg00x, &curr_rate);
	if (err < 0)
		goto error;
	if (rate == 0)
		rate = curr_rate;
	if (curr_rate != rate ||
	    amdtp_streaming_error(&dg00x->tx_stream) ||
	    amdtp_streaming_error(&dg00x->rx_stream)) {
		finish_session(dg00x);

		amdtp_stream_stop(&dg00x->tx_stream);
		amdtp_stream_stop(&dg00x->rx_stream);
		release_resources(dg00x);
	}


	if (!amdtp_stream_running(&dg00x->rx_stream)) {
		err = snd_dg00x_stream_set_local_rate(dg00x, rate);
		if (err < 0)
			goto error;

		err = keep_resources(dg00x, rate);
		if (err < 0)
			goto error;

		err = begin_session(dg00x);
		if (err < 0)
			goto error;

		err = amdtp_stream_start(&dg00x->rx_stream,
				dg00x->rx_resources.channel,
				fw_parent_device(dg00x->unit)->max_speed);
		if (err < 0)
			goto error;

		if (!amdtp_stream_wait_callback(&dg00x->rx_stream,
					      CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}


	if (!amdtp_stream_running(&dg00x->tx_stream)) {
		err = amdtp_stream_start(&dg00x->tx_stream,
				dg00x->tx_resources.channel,
				fw_parent_device(dg00x->unit)->max_speed);
		if (err < 0)
			goto error;

		if (!amdtp_stream_wait_callback(&dg00x->tx_stream,
					      CALLBACK_TIMEOUT)) {
			err = -ETIMEDOUT;
			goto error;
		}
	}
end:
	return err;
error:
	finish_session(dg00x);

	amdtp_stream_stop(&dg00x->tx_stream);
	amdtp_stream_stop(&dg00x->rx_stream);
	release_resources(dg00x);

	return err;
}
