a2dp_cancel(struct audio_device *dev, unsigned int id)
{
	struct a2dp_setup *setup;
	GSList *l;

	setup = find_setup_by_dev(dev);
	if (!setup)
		return FALSE;

	for (l = setup->cb; l != NULL; l = g_slist_next(l)) {
		struct a2dp_setup_cb *cb = l->data;

		if (cb->id != id)
			continue;

		setup_ref(setup);
		setup_cb_free(cb);

		if (!setup->cb) {
			DBG("aborting setup %p", setup);
			avdtp_abort(setup->session, setup->stream);
			return TRUE;
		}

		setup_unref(setup);
		return TRUE;
	}

	return FALSE;
}
