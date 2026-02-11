manager_find_devices(const char *path,
					const bdaddr_t *src,
					const bdaddr_t *dst,
					const char *interface,
					gboolean connected)
{
	GSList *result = NULL;
	GSList *l;

	for (l = devices; l != NULL; l = l->next) {
		struct audio_device *dev = l->data;

		if ((path && (strcmp(path, "")) && strcmp(dev->path, path)))
			continue;

		if ((src && bacmp(src, BDADDR_ANY)) && bacmp(&dev->src, src))
			continue;

		if ((dst && bacmp(dst, BDADDR_ANY)) && bacmp(&dev->dst, dst))
			continue;

		if (interface && !strcmp(AUDIO_HEADSET_INTERFACE, interface)
				&& !dev->headset)
			continue;

		if (interface && !strcmp(AUDIO_GATEWAY_INTERFACE, interface)
				&& !dev->gateway)
			continue;

		if (interface && !strcmp(AUDIO_SINK_INTERFACE, interface)
				&& !dev->sink)
			continue;

		if (interface && !strcmp(AUDIO_SOURCE_INTERFACE, interface)
				&& !dev->source)
			continue;

		if (interface && !strcmp(AUDIO_CONTROL_INTERFACE, interface)
				&& !dev->control)
			continue;

		if (connected && !audio_device_is_active(dev, interface))
			continue;

		result = g_slist_append(result, dev);
	}

	return result;
}
