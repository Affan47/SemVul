DtsDropPictures( HANDLE  hDevice ,
                uint32_t Pictures )
{
	BC_STATUS			sts = BC_STS_SUCCESS;
	DTS_LIB_CONTEXT		*Ctx = NULL;

	DTS_GET_CTX(hDevice,Ctx);
	if (Ctx->State == BC_DEC_STATE_CLOSE)
	{
		return BC_STS_DEC_NOT_OPEN;
	}

	if (Ctx->State == BC_DEC_STATE_STOP || Ctx->State == BC_DEC_STATE_FLUSH)
	{
		return BC_STS_DEC_NOT_STARTED;
	}

	sts = DtsFWDrop(hDevice,Pictures);

	if(sts != BC_STS_SUCCESS)
	{
		DebugLog_Trace(LDIL_DBG,"DtsDropPictures: Set Picture Mode Failed, %d\n",Pictures);
		return sts;
	}

	return BC_STS_SUCCESS;
}
