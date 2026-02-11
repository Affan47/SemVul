run_connect_cb(struct audio_device *dev, GError *err)
{
	struct gateway *gw = dev->gateway;
	GSList *l;

	for (l = gw->callbacks; l != NULL; l = l->next) {
		struct connect_cb *cb = l->data;
		cb->cb(dev, err, cb->cb_data);
	}

	g_slist_free_full(gw->callbacks, g_free);
	gw->callbacks = NULL;
}
