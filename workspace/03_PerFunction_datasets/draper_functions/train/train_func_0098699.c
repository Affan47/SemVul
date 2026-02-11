usbtv_audio_urb_received(struct urb *urb)
{
	struct usbtv *chip = urb->context;
	struct snd_pcm_substream *substream = chip->snd_substream;
	struct snd_pcm_runtime *runtime = substream->runtime;
	size_t i, frame_bytes, chunk_length, buffer_pos, period_pos;
	int period_elapsed;
	void *urb_current;

	switch (urb->status) {
	case 0:
	case -ETIMEDOUT:
		break;
	case -ENOENT:
	case -EPROTO:
	case -ECONNRESET:
	case -ESHUTDOWN:
		return;
	default:
		dev_warn(chip->dev, "unknown audio urb status %i\n",
			urb->status);
	}

	if (!atomic_read(&chip->snd_stream))
		return;

	frame_bytes = runtime->frame_bits >> 3;
	chunk_length = USBTV_CHUNK / frame_bytes;

	buffer_pos = chip->snd_buffer_pos;
	period_pos = chip->snd_period_pos;
	period_elapsed = 0;

	for (i = 0; i < urb->actual_length; i += USBTV_CHUNK_SIZE) {
		urb_current = urb->transfer_buffer + i + USBTV_AUDIO_HDRSIZE;

		if (buffer_pos + chunk_length >= runtime->buffer_size) {
			size_t cnt = (runtime->buffer_size - buffer_pos) *
				frame_bytes;
			memcpy(runtime->dma_area + buffer_pos * frame_bytes,
				urb_current, cnt);
			memcpy(runtime->dma_area, urb_current + cnt,
				chunk_length * frame_bytes - cnt);
		} else {
			memcpy(runtime->dma_area + buffer_pos * frame_bytes,
				urb_current, chunk_length * frame_bytes);
		}

		buffer_pos += chunk_length;
		period_pos += chunk_length;

		if (buffer_pos >= runtime->buffer_size)
			buffer_pos -= runtime->buffer_size;

		if (period_pos >= runtime->period_size) {
			period_pos -= runtime->period_size;
			period_elapsed = 1;
		}
	}

	snd_pcm_stream_lock(substream);

	chip->snd_buffer_pos = buffer_pos;
	chip->snd_period_pos = period_pos;

	snd_pcm_stream_unlock(substream);

	if (period_elapsed)
		snd_pcm_period_elapsed(substream);

	usb_submit_urb(urb, GFP_ATOMIC);
}
