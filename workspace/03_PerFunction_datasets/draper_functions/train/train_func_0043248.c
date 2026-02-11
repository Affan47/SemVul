ipr_wait_for_ops(struct ipr_ioa_cfg *ioa_cfg, void *device,
			    int (*match)(struct ipr_cmnd *, void *))
{
	struct ipr_cmnd *ipr_cmd;
	int wait;
	unsigned long flags;
	struct ipr_hrr_queue *hrrq;
	signed long timeout = IPR_ABORT_TASK_TIMEOUT;
	DECLARE_COMPLETION_ONSTACK(comp);

	ENTER;
	do {
		wait = 0;

		for_each_hrrq(hrrq, ioa_cfg) {
			spin_lock_irqsave(hrrq->lock, flags);
			list_for_each_entry(ipr_cmd, &hrrq->hrrq_pending_q, queue) {
				if (match(ipr_cmd, device)) {
					ipr_cmd->eh_comp = &comp;
					wait++;
				}
			}
			spin_unlock_irqrestore(hrrq->lock, flags);
		}

		if (wait) {
			timeout = wait_for_completion_timeout(&comp, timeout);

			if (!timeout) {
				wait = 0;

				for_each_hrrq(hrrq, ioa_cfg) {
					spin_lock_irqsave(hrrq->lock, flags);
					list_for_each_entry(ipr_cmd, &hrrq->hrrq_pending_q, queue) {
						if (match(ipr_cmd, device)) {
							ipr_cmd->eh_comp = NULL;
							wait++;
						}
					}
					spin_unlock_irqrestore(hrrq->lock, flags);
				}

				if (wait)
					dev_err(&ioa_cfg->pdev->dev, "Timed out waiting for aborted commands\n");
				LEAVE;
				return wait ? FAILED : SUCCESS;
			}
		}
	} while (wait);

	LEAVE;
	return SUCCESS;
}
