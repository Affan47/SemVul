DtsCancelFetchOutInt(DTS_LIB_CONTEXT *Ctx)
{
	bool pend = false;
	uint32_t cnt;

	if(!(DtsIsPend(Ctx))){
		return BC_STS_SUCCESS;
	}

	Ctx->CancelWaiting = 1;


	cnt = BC_PROC_OUTPUT_TIMEOUT / 100;

	do{
		usleep(100 * 1000);
		pend = DtsIsPend(Ctx);
	}while( (pend) && (cnt--) );

	if(pend){
		DebugLog_Trace(LDIL_DBG,"DtsCancelFetchOutInt: TimeOut\n");
		Ctx->CancelWaiting = 0;
		return BC_STS_TIMEOUT;
	}

	Ctx->CancelWaiting = 0;

	return BC_STS_SUCCESS;
}
