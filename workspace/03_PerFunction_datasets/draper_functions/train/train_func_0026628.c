mptbase_sas_persist_operation(MPT_ADAPTER *ioc, u8 persist_opcode)
{
	SasIoUnitControlRequest_t	*sasIoUnitCntrReq;
	SasIoUnitControlReply_t		*sasIoUnitCntrReply;
	MPT_FRAME_HDR			*mf = NULL;
	MPIHeader_t			*mpi_hdr;
	int				ret = 0;
	unsigned long 	 		timeleft;

	mutex_lock(&ioc->mptbase_cmds.mutex);


	memset(ioc->mptbase_cmds.reply, 0 , MPT_DEFAULT_FRAME_SIZE);
	INITIALIZE_MGMT_STATUS(ioc->mptbase_cmds.status)


	switch(persist_opcode) {

	case MPI_SAS_OP_CLEAR_NOT_PRESENT:
	case MPI_SAS_OP_CLEAR_ALL_PERSISTENT:
		break;

	default:
		ret = -1;
		goto out;
	}

	printk(KERN_DEBUG  "%s: persist_opcode=%x\n",
		__func__, persist_opcode);


	if ((mf = mpt_get_msg_frame(mpt_base_index, ioc)) == NULL) {
		printk(KERN_DEBUG "%s: no msg frames!\n", __func__);
		ret = -1;
		goto out;
        }

	mpi_hdr = (MPIHeader_t *) mf;
	sasIoUnitCntrReq = (SasIoUnitControlRequest_t *)mf;
	memset(sasIoUnitCntrReq,0,sizeof(SasIoUnitControlRequest_t));
	sasIoUnitCntrReq->Function = MPI_FUNCTION_SAS_IO_UNIT_CONTROL;
	sasIoUnitCntrReq->MsgContext = mpi_hdr->MsgContext;
	sasIoUnitCntrReq->Operation = persist_opcode;

	mpt_put_msg_frame(mpt_base_index, ioc, mf);
	timeleft = wait_for_completion_timeout(&ioc->mptbase_cmds.done, 10*HZ);
	if (!(ioc->mptbase_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) {
		ret = -ETIME;
		printk(KERN_DEBUG "%s: failed\n", __func__);
		if (ioc->mptbase_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET)
			goto out;
		if (!timeleft) {
			printk(MYIOC_s_WARN_FMT
			       "Issuing Reset from %s!!, doorbell=0x%08x\n",
			       ioc->name, __func__, mpt_GetIocState(ioc, 0));
			mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
			mpt_free_msg_frame(ioc, mf);
		}
		goto out;
	}

	if (!(ioc->mptbase_cmds.status & MPT_MGMT_STATUS_RF_VALID)) {
		ret = -1;
		goto out;
	}

	sasIoUnitCntrReply =
	    (SasIoUnitControlReply_t *)ioc->mptbase_cmds.reply;
	if (le16_to_cpu(sasIoUnitCntrReply->IOCStatus) != MPI_IOCSTATUS_SUCCESS) {
		printk(KERN_DEBUG "%s: IOCStatus=0x%X IOCLogInfo=0x%X\n",
		    __func__, sasIoUnitCntrReply->IOCStatus,
		    sasIoUnitCntrReply->IOCLogInfo);
		printk(KERN_DEBUG "%s: failed\n", __func__);
		ret = -1;
	} else
		printk(KERN_DEBUG "%s: success\n", __func__);
 out:

	CLEAR_MGMT_STATUS(ioc->mptbase_cmds.status)
	mutex_unlock(&ioc->mptbase_cmds.mutex);
	return ret;
}
