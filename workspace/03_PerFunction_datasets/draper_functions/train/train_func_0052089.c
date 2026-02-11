setup_new(struct avdtp *session)
{
	struct audio_device *dev;
	struct a2dp_setup *setup;

	dev = a2dp_get_dev(session);
	if (!dev) {
		error("Unable to create setup");
		return NULL;
	}

	setup = g_new0(struct a2dp_setup, 1);
	setup->session = avdtp_ref(session);
	setup->dev = a2dp_get_dev(session);
	setups = g_slist_append(setups, setup);

	return setup;
}
