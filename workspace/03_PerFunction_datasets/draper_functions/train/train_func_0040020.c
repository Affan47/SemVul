DtsFetchOutInterruptible(DTS_LIB_CONTEXT *Ctx, BC_DTS_PROC_OUT *pOut, uint32_t dwTimeout)
{
	BC_STATUS sts = BC_STS_SUCCESS;

	if(!Ctx ||  !pOut)
		return BC_STS_INV_ARG;

	if(DtsIsPend(Ctx)){
		DebugLog_Trace(LDIL_DBG,"DtsFetchOutInterruptible: ProcOutput Pending.. \n");
		return BC_STS_BUSY;
	}

	DtsIncPend(Ctx);

	memset(Ctx->pOutData,0,sizeof(*Ctx->pOutData));

	sts=DtsDrvCmd(Ctx,BCM_IOC_FETCH_RXBUFF,0,Ctx->pOutData,FALSE);

	if(sts == BC_STS_SUCCESS)
	{
		DtsSetupProcOutInfo(Ctx,pOut,Ctx->pOutData);
		sts = Ctx->pOutData->RetSts;
		if(sts != BC_STS_SUCCESS)
		{
			DtsDecPend(Ctx);
		}

	}else{
		DebugLog_Trace(LDIL_DBG,"DtsFetchOutInterruptible: Failed:%x\n",sts);
		DtsDecPend(Ctx);
	}

	if(!Ctx->CancelWaiting)
		return sts;


	if(sts == BC_STS_SUCCESS){
		sts = BC_STS_IO_USER_ABORT;
		DtsRelRxBuff(Ctx,&Ctx->pOutData->u.RxBuffs,FALSE);
	}

	return sts;
}
