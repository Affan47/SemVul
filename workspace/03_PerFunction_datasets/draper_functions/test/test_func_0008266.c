snic_abort_cmd(struct scsi_cmnd *sc)
{
	struct snic *snic = shost_priv(sc->device->host);
	int ret = SUCCESS, tag = snic_cmd_tag(sc);
	u32 start_time = jiffies;

	SNIC_SCSI_DBG(snic->shost, "abt_cmd:sc %p :0x%x :req = %p :tag = %d\n",
		       sc, sc->cmnd[0], sc->request, tag);

	if (unlikely(snic_get_state(snic) != SNIC_ONLINE)) {
		SNIC_HOST_ERR(snic->shost,
			      "abt_cmd: tag %x Parent Devs are not rdy\n",
			      tag);
		ret = FAST_IO_FAIL;

		goto abort_end;
	}


	ret = snic_send_abort_and_wait(snic, sc);
	if (ret)
		goto abort_end;

	ret = snic_abort_finish(snic, sc);

abort_end:
	SNIC_TRC(snic->shost->host_no, tag, (ulong) sc,
		 jiffies_to_msecs(jiffies - start_time), 0,
		 SNIC_TRC_CMD(sc), SNIC_TRC_CMD_STATE_FLAGS(sc));

	SNIC_SCSI_DBG(snic->shost,
		      "abts: Abort Req Status = %s\n",
		      (ret == SUCCESS) ? "SUCCESS" :
		       ((ret == FAST_IO_FAIL) ? "FAST_IO_FAIL" : "FAILED"));

	return ret;
}
