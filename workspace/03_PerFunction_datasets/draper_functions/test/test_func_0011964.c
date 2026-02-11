DtsFetchMdata(DTS_LIB_CONTEXT *Ctx, uint16_t snum, BC_DTS_PROC_OUT *pout)
{
	uint32_t		InTag;
	DTS_INPUT_MDATA		*temp=NULL;
	BC_STATUS	sts = BC_STS_NO_DATA;
	int16_t tsnum = 0;
	uint32_t i = 0;

	if(!Ctx || !pout){
		return BC_STS_INV_ARG;
	}

	if(!snum){

		pout->PicInfo.timeStamp = 0;
		DebugLog_Trace(LDIL_DBG,"ZeroSnum \n");
		return BC_STS_NO_DATA;
	}

	InTag = DtsMdataGetIntTag(Ctx,snum);
	temp = Ctx->MDPendHead;

	DtsLock(Ctx);
	while(temp && temp != DTS_MDATA_PEND_LINK(Ctx)){
		if(temp->IntTag == InTag){
			pout->PicInfo.timeStamp = temp->appTimeStamp;
			sts = BC_STS_SUCCESS;
			DtsRemoveMdata(Ctx, temp, FALSE);


			Ctx->MDLastFetchTag = InTag;
			break;
		}
		temp = temp->flink;
	}
	DtsUnLock(Ctx);


	if(sts == BC_STS_SUCCESS) {
		for(i = 0; i < 100; i++) {
			tsnum = snum - (10 + i);
			if(tsnum < 0)
				break;
			InTag = DtsMdataGetIntTag(Ctx, tsnum);
			temp = Ctx->MDPendHead;
			DtsLock(Ctx);
			while(temp && temp != DTS_MDATA_PEND_LINK(Ctx)){
				if(temp->IntTag == InTag){
					DtsRemoveMdata(Ctx, temp, FALSE);
					break;
				}
				temp = temp->flink;
			}
			DtsUnLock(Ctx);
		}
	}

	return sts;
}
