DtsSetupConfig(DTS_LIB_CONTEXT *Ctx, uint32_t did, uint32_t rid, uint32_t FixFlags)
{
	Ctx->DevId = did;
	Ctx->hwRevId = rid;
	Ctx->FixFlags = FixFlags;

	if(Ctx->DevId == BC_PCI_DEVID_LINK){
		Ctx->RegCfg.DbgOptions = BC_DTS_DEF_OPTIONS_LINK;
	}else{
		Ctx->RegCfg.DbgOptions = BC_DTS_DEF_OPTIONS;
	}
	DtsGetBCRegConfig(Ctx);


	if( (Ctx->DevId == BC_PCI_DEVID_LINK)&& (!(Ctx->RegCfg.DbgOptions & BC_BIT(5))) ){

		Ctx->RegCfg.DbgOptions |= BC_BIT(5);
	}


	Ctx->capInfo.ColorCaps.Count = 0;
	if (Ctx->DevId == BC_PCI_DEVID_LINK)
	{
		Ctx->capInfo.ColorCaps.Count =3;
		Ctx->capInfo.ColorCaps.OutFmt[0] = OUTPUT_MODE420;
		Ctx->capInfo.ColorCaps.OutFmt[1] = OUTPUT_MODE422_YUY2;
		Ctx->capInfo.ColorCaps.OutFmt[2] = OUTPUT_MODE422_UYVY;
		Ctx->capInfo.flags = PES_CONV_SUPPORT;


		Ctx->capInfo.DecCaps = BC_DEC_FLAGS_H264 | BC_DEC_FLAGS_MPEG2 | BC_DEC_FLAGS_VC1;
	}
	else if(Ctx->DevId == BC_PCI_DEVID_DOZER)
	{
		Ctx->capInfo.ColorCaps.Count =1;
		Ctx->capInfo.ColorCaps.OutFmt[0] = OUTPUT_MODE420;
		Ctx->capInfo.flags = PES_CONV_SUPPORT;


		Ctx->capInfo.DecCaps = BC_DEC_FLAGS_H264 | BC_DEC_FLAGS_MPEG2 | BC_DEC_FLAGS_VC1;
	}

	Ctx->capInfo.Reserved1 = NULL;

	return BC_STS_SUCCESS;
}
