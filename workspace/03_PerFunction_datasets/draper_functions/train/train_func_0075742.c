DtsStopDecoder(
    HANDLE  hDevice
	)
{
	BC_STATUS	sts = BC_STS_SUCCESS;

	DTS_LIB_CONTEXT		*Ctx = NULL;
	DTS_GET_CTX(hDevice,Ctx);

	if (!DtsChkPID(Ctx->ProcessID))
		return BC_STS_ERROR;

	if (Ctx->State == BC_DEC_STATE_CLOSE || Ctx->State == BC_DEC_STATE_STOP)
	{
		return BC_STS_SUCCESS;
	}


	if(Ctx->DevId == BC_PCI_DEVID_LINK && Ctx->hw_paused) {
		DtsFWPauseVideo(hDevice,eC011_PAUSE_MODE_OFF);
		Ctx->hw_paused = false;
	}
	DtsCancelFetchOutInt(Ctx);

	sts = DtsFWStopVideo(hDevice,Ctx->OpenRsp.channelId, FALSE);

	sts = DtsFlushRxCapture(hDevice, false);

	Ctx->State = BC_DEC_STATE_STOP;

	return sts;
}
