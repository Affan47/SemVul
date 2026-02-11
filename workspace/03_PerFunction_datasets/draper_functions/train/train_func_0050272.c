DtsReleaseChannel(HANDLE  hDevice, uint32_t ChannelID, bool Stop)
{
	BC_STATUS	sts = BC_STS_SUCCESS;
	if(Stop){
		sts = DtsFWStopVideo(hDevice, ChannelID, true);
		if(sts != BC_STS_SUCCESS){
			DebugLog_Trace(LDIL_DBG,"DtsReleaseChannel: StopVideoFailed Ignoring error\n");
		}
	}
	sts = DtsFWCloseChannel(hDevice, ChannelID);
	if(sts != BC_STS_SUCCESS){
		DebugLog_Trace(LDIL_DBG,"DtsReleaseChannel: DtsFWCloseChannel Failed\n");
	}

	return sts;
}
