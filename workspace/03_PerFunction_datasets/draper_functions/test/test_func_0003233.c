DtsFPGARegisterRead(
    HANDLE		hDevice,
    uint32_t			offset,
    uint32_t			*Value
    )
{
	BC_IOCTL_DATA *pIocData = NULL;
	BC_CMD_REG_ACC	*reg_acc_read;
	DTS_LIB_CONTEXT		*Ctx = NULL;
	BC_STATUS	sts = BC_STS_SUCCESS;


	DTS_GET_CTX(hDevice,Ctx);

	if(!(pIocData = DtsAllocIoctlData(Ctx)))
		return BC_STS_INSUFF_RES;


	reg_acc_read = (BC_CMD_REG_ACC *) &pIocData->u.regAcc;


	reg_acc_read->Offset	= offset;
	reg_acc_read->Value		= 0;

	if( (sts=DtsDrvCmd(Ctx,BCM_IOC_FPGA_RD,0,pIocData,FALSE)) != BC_STS_SUCCESS){
		DtsRelIoctlData(Ctx,pIocData);
		DebugLog_Trace(LDIL_DBG,"DtsFPGARegisterRead: Ioctl failed: %d\n",sts);
		return sts;
	}

	*Value = reg_acc_read->Value;

	DtsRelIoctlData(Ctx,pIocData);

	return BC_STS_SUCCESS;
}
