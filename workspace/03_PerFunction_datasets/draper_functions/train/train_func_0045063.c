path_unregister(void *data)
{
	struct audio_device *dev = data;
	struct headset *hs = dev->headset;

	if (hs->state > HEADSET_STATE_DISCONNECTED) {
		DBG("Headset unregistered while device was connected!");
		headset_shutdown(dev);
	}

	DBG("Unregistered interface %s on path %s",
		AUDIO_HEADSET_INTERFACE, dev->path);

	headset_free(dev);
}
