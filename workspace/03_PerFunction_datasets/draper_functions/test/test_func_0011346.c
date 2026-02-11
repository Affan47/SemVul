DtsFlushRxCapture(
				HANDLE  hDevice,
				BOOL	bDiscardOnly)
{
	DTS_LIB_CONTEXT		*Ctx = NULL;
	BC_STATUS			Sts;
	BC_IOCTL_DATA *pIocData = NULL;

	DTS_GET_CTX(hDevice,Ctx);

	if (!Ctx->bMapOutBufDone)
	{
		return BC_STS_SUCCESS;
	}

	if (!DtsChkPID(Ctx->ProcessID))
		return BC_STS_ERROR;

	if (Ctx->State == BC_DEC_STATE_CLOSE)
	{
		return BC_STS_DEC_NOT_OPEN;
	}

	if(!(pIocData = DtsAllocIoctlData(Ctx)))
		return BC_STS_INSUFF_RES;

	pIocData->u.FlushRxCap.bDiscardOnly = bDiscardOnly;
	Sts = DtsDrvCmd(Ctx,BCM_IOC_FLUSH_RX_CAP, 0, pIocData, TRUE);

	if(bDiscardOnly == false)
	{
		Ctx->bMapOutBufDone = false;
    }

	return Sts;
}
