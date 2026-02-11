headset_add_nrec_cb(struct audio_device *dev,
					headset_nrec_cb cb, void *user_data)
{
	struct headset *hs = dev->headset;
	struct headset_nrec_callback *nrec_cb;
	static unsigned int id = 0;

	nrec_cb = g_new(struct headset_nrec_callback, 1);
	nrec_cb->cb = cb;
	nrec_cb->user_data = user_data;
	nrec_cb->id = ++id;

	hs->nrec_cbs = g_slist_prepend(hs->nrec_cbs, nrec_cb);

	return nrec_cb->id;
}
