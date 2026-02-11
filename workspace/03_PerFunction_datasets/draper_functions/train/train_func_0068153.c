dvcman_create_channel(IWTSVirtualChannelManager* pChannelMgr, uint32 ChannelId, const char* ChannelName)
{
	DVCMAN* dvcman = (DVCMAN*)pChannelMgr;
	int i;
	DVCMAN_LISTENER* listener;
	DVCMAN_CHANNEL* channel;
	struct dvcman_channel_list_item* item;
	int bAccept;
	IWTSVirtualChannelCallback* pCallback;

	for (i = 0; i < dvcman->num_listeners; i++)
	{
		listener = (DVCMAN_LISTENER*)dvcman->listeners[i];
		if (strcmp(listener->channel_name, ChannelName) == 0)
		{
			item = dvcman_channel_list_item_new();
			channel = (DVCMAN_CHANNEL*)item;
			channel->iface.Write = dvcman_write_channel;
			channel->iface.Close = dvcman_close_channel_iface;
			channel->dvcman = dvcman;
			channel->channel_id = ChannelId;

			bAccept = 1;
			pCallback = NULL;
			if (listener->listener_callback->OnNewChannelConnection(listener->listener_callback,
				(IWTSVirtualChannel*)channel, NULL, &bAccept, &pCallback) == 0 && bAccept == 1)
			{
				DEBUG_PRINT("DVC", "listener %s created new channel %d",
					listener->channel_name, channel->channel_id);
				channel->channel_callback = pCallback;
				dvcman_channel_list_add(dvcman->channels, item);
				return 0;
			}
			else
			{
				DEBUG_WARN("channel rejected by plugin");
				dvcman_channel_list_item_free(item);
				return 1;
			}
		}
	}
	return 1;
}
