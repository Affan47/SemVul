DtsSetInputFormat(
    HANDLE hDevice,
    BC_INPUT_FORMAT *pInputFormat
    )
{
	DTS_LIB_CONTEXT *Ctx = NULL;
	uint32_t videoAlgo = BC_VID_ALGO_H264;
	uint32_t	ScaledWidth = 0;

	DTS_GET_CTX(hDevice,Ctx);

	Ctx->VidParams.MediaSubType = pInputFormat->mSubtype;
	Ctx->VidParams.WidthInPixels = pInputFormat->width;
	Ctx->VidParams.HeightInPixels = pInputFormat->height;
	if (pInputFormat->startCodeSz)
		Ctx->VidParams.StartCodeSz = pInputFormat->startCodeSz;
	else
		Ctx->VidParams.StartCodeSz = BRCM_START_CODE_SIZE;

	if (pInputFormat->metaDataSz)
	{
		if(Ctx->VidParams.pMetaData){
			DebugLog_Trace(LDIL_DBG,"deleting buffer\n");
			free(Ctx->VidParams.pMetaData);
		}
		Ctx->VidParams.pMetaData = (uint8_t*)malloc(pInputFormat->metaDataSz);
		memcpy(Ctx->VidParams.pMetaData, pInputFormat->pMetaData, pInputFormat->metaDataSz);

		Ctx->VidParams.MetaDataSz = pInputFormat->metaDataSz;
	}

	if(Ctx->VidParams.MediaSubType == BC_MSUBTYPE_H264 || Ctx->VidParams.MediaSubType== BC_MSUBTYPE_AVC1)
	{
		videoAlgo = BC_VID_ALGO_H264;
	}
	else if (Ctx->VidParams.MediaSubType==BC_MSUBTYPE_DIVX)
	{
		videoAlgo = BC_VID_ALGO_DIVX;
	}
	else if(Ctx->VidParams.MediaSubType == BC_MSUBTYPE_MPEG2VIDEO )
	{
		videoAlgo = BC_VID_ALGO_MPEG2;
	}
	else if(Ctx->VidParams.MediaSubType == BC_MSUBTYPE_WVC1 || Ctx->VidParams.MediaSubType == BC_MSUBTYPE_WMVA ||Ctx->VidParams.MediaSubType == BC_MSUBTYPE_VC1)
	{
		videoAlgo = BC_VID_ALGO_VC1;
	}
	else  if (Ctx->VidParams.MediaSubType == BC_MSUBTYPE_WMV3)
	{
		videoAlgo = BC_VID_ALGO_VC1MP;
	}

	if (Ctx->DevId == BC_PCI_DEVID_FLEA || Ctx->VidParams.MediaSubType == BC_MSUBTYPE_WMV3)
		Ctx->VidParams.StreamType = BC_STREAM_TYPE_PES;
	else
		Ctx->VidParams.StreamType = BC_STREAM_TYPE_ES;

	DtsSetVideoParams(hDevice, videoAlgo, pInputFormat->FGTEnable, pInputFormat->MetaDataEnable, pInputFormat->Progressive, pInputFormat->OptFlags);
	DtsSetPESConverter(hDevice);

	if(Ctx->DevId == BC_PCI_DEVID_FLEA)
	{
		if(Ctx->SingleThreadedAppMode) {
			pInputFormat->bEnableScaling = true;
			pInputFormat->ScalingParams.sWidth = 1280;
		}
		if(pInputFormat->bEnableScaling) {
			if((pInputFormat->ScalingParams.sWidth > 1920)||
			   (pInputFormat->ScalingParams.sWidth < 128))
				ScaledWidth = 1280;
			else
				ScaledWidth = pInputFormat->ScalingParams.sWidth;

			Ctx->EnableScaling = (ScaledWidth << 20) | (ScaledWidth << 8) |
					     pInputFormat->bEnableScaling;
		} else {
			Ctx->EnableScaling = 0;
		}

		Ctx->bEnable720pDropHalf = 0;
	}

	return DtsCheckProfile(hDevice);
}
