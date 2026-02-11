gateway_cancel_stream(struct audio_device *dev, unsigned int id)
{
	struct gateway *gw = dev->gateway;
	GSList *l;
	struct connect_cb *cb = NULL;

	for (l = gw->callbacks; l != NULL; l = l->next) {
		struct connect_cb *tmp = l->data;

		if (tmp->id == id) {
			cb = tmp;
			break;
		}
	}

	if (!cb)
		return FALSE;

	gw->callbacks = g_slist_remove(gw->callbacks, cb);
	g_free(cb);

	gateway_suspend_stream(dev);

	return TRUE;
}
