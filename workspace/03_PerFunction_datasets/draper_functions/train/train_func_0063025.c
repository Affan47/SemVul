audio_tx_completion(struct most_interface *iface, int channel_id)
{
	struct channel *channel = get_channel(iface, channel_id);

	if (!channel) {
		pr_err("sound_tx_completion(), invalid channel %d\n",
		       channel_id);
		return -EINVAL;
	}

	wake_up_interruptible(&channel->playback_waitq);

	return 0;
}
