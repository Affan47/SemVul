snic_abort_finish(struct snic *snic, struct scsi_cmnd *sc)
{
	struct snic_req_info *rqi = NULL;
	spinlock_t *io_lock = NULL;
	unsigned long flags;
	int ret = 0, tag = snic_cmd_tag(sc);

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);
	rqi = (struct snic_req_info *) CMD_SP(sc);
	if (!rqi) {
		atomic64_inc(&snic->s_stats.io.req_null);
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TERM_REQ_NULL;

		SNIC_SCSI_DBG(snic->shost,
			      "abt_fini:req info is null tag 0x%x, sc 0x%p flags 0x%llx\n",
			      tag, sc, CMD_FLAGS(sc));
		ret = FAILED;

		goto abort_fail;
	}

	rqi->abts_done = NULL;

	ret = FAILED;


	switch (CMD_ABTS_STATUS(sc)) {
	case SNIC_INVALID_CODE:

		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TIMEDOUT;
		atomic64_inc(&snic->s_stats.abts.drv_tmo);
		SNIC_SCSI_DBG(snic->shost,
			      "abt_fini:sc %p Tag %x Driver Timeout.flags 0x%llx\n",
			      sc, snic_cmd_tag(sc), CMD_FLAGS(sc));

		rqi = NULL;

		goto abort_fail;

	case SNIC_STAT_IO_SUCCESS:
	case SNIC_STAT_IO_NOT_FOUND:
		ret = SUCCESS;
		break;

	default:

		ret = FAILED;
		break;
	}

	CMD_SP(sc) = NULL;
	SNIC_HOST_INFO(snic->shost,
		       "abt_fini: Tag %x, Cmpl Status %s flags 0x%llx\n",
		       tag, snic_io_status_to_str(CMD_ABTS_STATUS(sc)),
		       CMD_FLAGS(sc));

abort_fail:
	spin_unlock_irqrestore(io_lock, flags);
	if (rqi)
		snic_release_req_buf(snic, rqi, sc);

	return ret;
}
