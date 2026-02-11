mvs_sata_done(struct mvs_info *mvi, struct sas_task *task,
			u32 slot_idx, int err)
{
	struct mvs_device *mvi_dev = task->dev->lldd_dev;
	struct task_status_struct *tstat = &task->task_status;
	struct ata_task_resp *resp = (struct ata_task_resp *)tstat->buf;
	int stat = SAM_STAT_GOOD;


	resp->frame_len = sizeof(struct dev_to_host_fis);
	memcpy(&resp->ending_fis[0],
	       SATA_RECEIVED_D2H_FIS(mvi_dev->taskfileset),
	       sizeof(struct dev_to_host_fis));
	tstat->buf_valid_size = sizeof(*resp);
	if (unlikely(err)) {
		if (unlikely(err & CMD_ISS_STPD))
			stat = SAS_OPEN_REJECT;
		else
			stat = SAS_PROTO_RESPONSE;
       }

	return stat;
}
