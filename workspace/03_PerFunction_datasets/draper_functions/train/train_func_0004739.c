sh_mmcif_timeout_work(struct work_struct *work)
{
	struct delayed_work *d = container_of(work, struct delayed_work, work);
	struct sh_mmcif_host *host = container_of(d, struct sh_mmcif_host, timeout_work);
	struct mmc_request *mrq = host->mrq;
	struct device *dev = sh_mmcif_host_to_dev(host);
	unsigned long flags;

	if (host->dying)

		return;

	spin_lock_irqsave(&host->lock, flags);
	if (host->state == STATE_IDLE) {
		spin_unlock_irqrestore(&host->lock, flags);
		return;
	}

	dev_err(dev, "Timeout waiting for %u on CMD%u\n",
		host->wait_for, mrq->cmd->opcode);

	host->state = STATE_TIMEOUT;
	spin_unlock_irqrestore(&host->lock, flags);


	switch (host->wait_for) {
	case MMCIF_WAIT_FOR_CMD:
		mrq->cmd->error = sh_mmcif_error_manage(host);
		break;
	case MMCIF_WAIT_FOR_STOP:
		mrq->stop->error = sh_mmcif_error_manage(host);
		break;
	case MMCIF_WAIT_FOR_MREAD:
	case MMCIF_WAIT_FOR_MWRITE:
	case MMCIF_WAIT_FOR_READ:
	case MMCIF_WAIT_FOR_WRITE:
	case MMCIF_WAIT_FOR_READ_END:
	case MMCIF_WAIT_FOR_WRITE_END:
		mrq->data->error = sh_mmcif_error_manage(host);
		break;
	default:
		BUG();
	}

	host->state = STATE_IDLE;
	host->wait_for = MMCIF_WAIT_FOR_REQUEST;
	host->mrq = NULL;
	mmc_request_done(host->mmc, mrq);
}
