DtsPendMdataGarbageCollect(DTS_LIB_CONTEXT *Ctx)
{
	DTS_INPUT_MDATA		*temp=NULL;
	int mdata_count = 0;

	if(!Ctx || !Ctx->MdataPoolPtr){
		return BC_STS_INV_ARG;
	}

	DtsLock(Ctx);


	temp = Ctx->MDPendHead;
	while(temp && temp != DTS_MDATA_PEND_LINK(Ctx)){

		if(mdata_count > (BC_INPUT_MDATA_POOL_SZ - BC_INPUT_MDATA_POOL_SZ_COLLECT)) {
			break;
		}
		DtsRemoveMdata(Ctx,temp,FALSE);
		temp = Ctx->MDPendHead;
		mdata_count++;
	}

	if (mdata_count)
		DebugLog_Trace(LDIL_DBG,"Clearing %d PendMdata entries \n", mdata_count);

	DtsUnLock(Ctx);

	return BC_STS_SUCCESS;
}
