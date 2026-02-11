MyVirtualChannelClose(uint32 openHandle)
{
	rdpChanMan* chan_man;
	struct chan_data* lchan;
	int index;

	DEBUG_CHANMAN("enter");
	chan_man = freerdp_chanman_find_by_open_handle(openHandle, &index);
	if ((chan_man == NULL) || (index < 0) || (index >= CHANNEL_MAX_COUNT))
	{
		DEBUG_CHANMAN("error bad chanhan");
		return CHANNEL_RC_BAD_CHANNEL_HANDLE;
	}
	lchan = chan_man->chans + index;
	if (lchan->flags != 2)
	{
		DEBUG_CHANMAN("error not open");
		return CHANNEL_RC_NOT_OPEN;
	}
	lchan->flags = 0;
	return CHANNEL_RC_OK;
}
