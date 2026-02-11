retire_playback_urb(struct snd_usb_substream *subs,
			       struct urb *urb)
{
	unsigned long flags;
	struct snd_pcm_runtime *runtime = subs->pcm_substream->runtime;
	struct snd_usb_endpoint *ep = subs->data_endpoint;
	int processed = urb->transfer_buffer_length / ep->stride;
	int est_delay;


	if (!processed)
		return;

	spin_lock_irqsave(&subs->lock, flags);
	if (!subs->last_delay)
		goto out;

	est_delay = snd_usb_pcm_delay(subs, runtime->rate);

	if (processed > subs->last_delay)
		subs->last_delay = 0;
	else
		subs->last_delay -= processed;
	runtime->delay = subs->last_delay;


	if (abs(est_delay - subs->last_delay) * 1000 > runtime->rate * 2)
		dev_dbg_ratelimited(&subs->dev->dev,
			"delay: estimated %d, actual %d\n",
			est_delay, subs->last_delay);

	if (!subs->running) {


		subs->last_frame_number =
			usb_get_current_frame_number(subs->dev) & 0xff;
	}

 out:
	spin_unlock_irqrestore(&subs->lock, flags);
}
