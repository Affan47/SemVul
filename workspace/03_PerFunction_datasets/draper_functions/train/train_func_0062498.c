snic_reset(struct Scsi_Host *shost, struct scsi_cmnd *sc)
{
	struct snic *snic = shost_priv(shost);
	enum snic_state sv_state;
	unsigned long flags;
	int ret = FAILED;


	sv_state = snic_get_state(snic);

	spin_lock_irqsave(&snic->snic_lock, flags);
	if (snic_get_state(snic) == SNIC_FWRESET) {
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		SNIC_HOST_INFO(shost, "reset:prev reset is in progres\n");

		msleep(SNIC_HOST_RESET_TIMEOUT);
		ret = SUCCESS;

		goto reset_end;
	}

	snic_set_state(snic, SNIC_FWRESET);
	spin_unlock_irqrestore(&snic->snic_lock, flags);


	while (atomic_read(&snic->ios_inflight))
		schedule_timeout(msecs_to_jiffies(1));

	ret = snic_issue_hba_reset(snic, sc);
	if (ret) {
		SNIC_HOST_ERR(shost,
			      "reset:Host Reset Failed w/ err %d.\n",
			      ret);
		spin_lock_irqsave(&snic->snic_lock, flags);
		snic_set_state(snic, sv_state);
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		atomic64_inc(&snic->s_stats.reset.hba_reset_fail);
		ret = FAILED;

		goto reset_end;
	}

	ret = SUCCESS;

reset_end:
	return ret;
}
