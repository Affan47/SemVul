snd_ctl_ext_subscribe_events(snd_ctl_t *handle, int subscribe)
{
	snd_ctl_ext_t *ext = handle->private_data;

	if (subscribe < 0)
		return ext->subscribed;
	ext->subscribed = !!subscribe;
	if (ext->callback->subscribe_events)
		ext->callback->subscribe_events(ext, subscribe);
	return 0;
}
