endpoint_init_ag(struct media_endpoint *endpoint, int *err)
{
	GSList *list;
	GSList *l;

	endpoint->hs_watch = headset_add_state_cb(headset_state_changed,
								endpoint);
	list = manager_find_devices(NULL, &endpoint->adapter->src, BDADDR_ANY,
						AUDIO_HEADSET_INTERFACE, TRUE);

	for (l = list; l != NULL; l = l->next) {
		struct audio_device *dev = l->data;

		set_configuration(endpoint, dev, NULL, 0,
						headset_setconf_cb, dev, NULL);
	}

	g_slist_free(list);

	return TRUE;
}
