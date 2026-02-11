_base_display_reply_info(struct MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
{
	MPI2DefaultReply_t *mpi_reply;
	u16 ioc_status;
	u32 loginfo = 0;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);
	if (unlikely(!mpi_reply)) {
		pr_err(MPT3SAS_FMT "mpi_reply not valid at %s:%d/%s()!\n",
		    ioc->name, __FILE__, __LINE__, __func__);
		return;
	}
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus);

	if ((ioc_status & MPI2_IOCSTATUS_MASK) &&
	    (ioc->logging_level & MPT_DEBUG_REPLY)) {
		_base_sas_ioc_info(ioc , mpi_reply,
		   mpt3sas_base_get_msg_frame(ioc, smid));
	}

	if (ioc_status & MPI2_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE) {
		loginfo = le32_to_cpu(mpi_reply->IOCLogInfo);
		_base_sas_log_info(ioc, loginfo);
	}

	if (ioc_status || loginfo) {
		ioc_status &= MPI2_IOCSTATUS_MASK;
		mpt3sas_trigger_mpi(ioc, ioc_status, loginfo);
	}
}
