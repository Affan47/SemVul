MyVirtualChannelOpen(void* pInitHandle, uint32* pOpenHandle,
	char* pChannelName, PCHANNEL_OPEN_EVENT_FN pChannelOpenEventProc)
{
	rdpChanMan* chan_man;
	int index;
	struct chan_data* lchan;

	DEBUG_CHANMAN("enter");
	chan_man = ((rdpInitHandle*)pInitHandle)->chan_man;
	if (pOpenHandle == 0)
	{
		DEBUG_CHANMAN("error bad chanhan");
		return CHANNEL_RC_BAD_CHANNEL_HANDLE;
	}
	if (pChannelOpenEventProc == 0)
	{
		DEBUG_CHANMAN("error bad proc");
		return CHANNEL_RC_BAD_PROC;
	}
	if (!chan_man->is_connected)
	{
		DEBUG_CHANMAN("error not connected");
		return CHANNEL_RC_NOT_CONNECTED;
	}
	lchan = freerdp_chanman_find_chan_data_by_name(chan_man, pChannelName, &index);
	if (lchan == 0)
	{
		DEBUG_CHANMAN("error chan name");
		return CHANNEL_RC_UNKNOWN_CHANNEL_NAME;
	}
	if (lchan->flags == 2)
	{
		DEBUG_CHANMAN("error chan already open");
		return CHANNEL_RC_ALREADY_OPEN;
	}

	lchan->flags = 2;
	lchan->open_event_proc = pChannelOpenEventProc;
	*pOpenHandle = lchan->open_handle;
	return CHANNEL_RC_OK;
}
