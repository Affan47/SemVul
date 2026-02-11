svc_plugin_send_event(rdpSvcPlugin* plugin, FRDP_EVENT* event)
{
	uint32 error = 0;

	DEBUG_SVC("event_type %d", event->event_type);

	error = plugin->channel_entry_points.pVirtualChannelEventPush(plugin->priv->open_handle,
		event);
	if (error != CHANNEL_RC_OK)
		printf("svc_plugin_send_event: VirtualChannelEventPush failed %d\n", error);

	return error;
}
