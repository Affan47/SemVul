path_unregister(void *data)
{
	struct audio_device *dev = data;
	struct control *control = dev->control;

	DBG("Unregistered interface %s on path %s",
		AUDIO_CONTROL_INTERFACE, dev->path);

	if (control->session)
		avctp_disconnect(control->session);

	g_free(control);
	dev->control = NULL;
}
