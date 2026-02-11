DtsFWSetSingleField(
    HANDLE  hDevice,
	bool bSingleField
    )
{
	BC_STATUS	sts = BC_STS_SUCCESS;
	DecCmdChannelSingleField	*pAct;
	DecRspChannelSingleField	*pActRsp;

	DTS_LIB_CONTEXT		*Ctx = NULL;
	BC_IOCTL_DATA *pIocData = NULL;

	DTS_GET_CTX(hDevice,Ctx);

	if(Ctx->State == BC_DEC_STATE_CLOSE)
	{
		DebugLog_Trace(LDIL_DBG,"DtsFWSetSingleField: Channel Not Opened\n");
		return BC_STS_DEC_NOT_OPEN;
	}

	if(!(pIocData = DtsAllocIoctlData(Ctx)))
		return BC_STS_INSUFF_RES;


	pAct = (DecCmdChannelSingleField *)&pIocData->u.fwCmd.cmd;

	pAct->command = eCMD_C011_DEC_CHAN_SET_SINGLE_FIELD;
	pAct->sequence = ++Ctx->fwcmdseq;
	pAct->channelId = Ctx->OpenRsp.channelId;
	pAct->SingleField = bSingleField;

	if( (sts=DtsDrvCmd(Ctx,BCM_IOC_FW_CMD,1,pIocData,FALSE)) != BC_STS_SUCCESS){
		DebugLog_Trace(LDIL_DBG,"DtsFWSetSingleField: Ioctl failed: %d\n",sts);
		DtsRelIoctlData(Ctx,pIocData);
		return sts;
	}

	pActRsp = (DecRspChannelSingleField*)&pIocData->u.fwCmd.rsp;

	if(pActRsp->status){
		DebugLog_Trace(LDIL_DBG,"DtsFWSetSingleField: Set Single Field Failed %d\n",pActRsp->status);
		DtsRelIoctlData(Ctx,pIocData);
		return BC_STS_FW_CMD_ERR;
	}

	DtsRelIoctlData(Ctx,pIocData);

	return BC_STS_SUCCESS;
}
