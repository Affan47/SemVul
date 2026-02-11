ipr_initiate_ioa_reset(struct ipr_ioa_cfg *ioa_cfg,
				   enum ipr_shutdown_type shutdown_type)
{
	int i;

	if (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead)
		return;

	if (ioa_cfg->in_reset_reload) {
		if (ioa_cfg->sdt_state == GET_DUMP)
			ioa_cfg->sdt_state = WAIT_FOR_DUMP;
		else if (ioa_cfg->sdt_state == READ_DUMP)
			ioa_cfg->sdt_state = ABORT_DUMP;
	}

	if (ioa_cfg->reset_retries++ >= IPR_NUM_RESET_RELOAD_RETRIES) {
		dev_err(&ioa_cfg->pdev->dev,
			"IOA taken offline - error recovery failed\n");

		ioa_cfg->reset_retries = 0;
		for (i = 0; i < ioa_cfg->hrrq_num; i++) {
			spin_lock(&ioa_cfg->hrrq[i]._lock);
			ioa_cfg->hrrq[i].ioa_is_dead = 1;
			spin_unlock(&ioa_cfg->hrrq[i]._lock);
		}
		wmb();

		if (ioa_cfg->in_ioa_bringdown) {
			ioa_cfg->reset_cmd = NULL;
			ioa_cfg->in_reset_reload = 0;
			ipr_fail_all_ops(ioa_cfg);
			wake_up_all(&ioa_cfg->reset_wait_q);

			if (!ioa_cfg->hrrq[IPR_INIT_HRRQ].removing_ioa) {
				spin_unlock_irq(ioa_cfg->host->host_lock);
				scsi_unblock_requests(ioa_cfg->host);
				spin_lock_irq(ioa_cfg->host->host_lock);
			}
			return;
		} else {
			ioa_cfg->in_ioa_bringdown = 1;
			shutdown_type = IPR_SHUTDOWN_NONE;
		}
	}

	_ipr_initiate_ioa_reset(ioa_cfg, ipr_reset_shutdown_ioa,
				shutdown_type);
}
