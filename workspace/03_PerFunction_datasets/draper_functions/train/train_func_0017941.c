usdhi6_sd_bh(int irq, void *dev_id)
{
	struct usdhi6_host *host = dev_id;
	struct mmc_request *mrq;
	struct mmc_command *cmd;
	struct mmc_data *data;
	bool io_wait = false;

	cancel_delayed_work_sync(&host->timeout_work);

	mrq = host->mrq;
	if (!mrq)
		return IRQ_HANDLED;

	cmd = mrq->cmd;
	data = mrq->data;

	switch (host->wait) {
	case USDHI6_WAIT_FOR_REQUEST:

		return IRQ_HANDLED;
	case USDHI6_WAIT_FOR_CMD:

		io_wait = usdhi6_end_cmd(host);
		break;
	case USDHI6_WAIT_FOR_MREAD:

		io_wait = usdhi6_mread_block(host);
		break;
	case USDHI6_WAIT_FOR_READ:

		io_wait = usdhi6_read_block(host);
		break;
	case USDHI6_WAIT_FOR_MWRITE:

		io_wait = usdhi6_mwrite_block(host);
		break;
	case USDHI6_WAIT_FOR_WRITE:

		io_wait = usdhi6_write_block(host);
		break;
	case USDHI6_WAIT_FOR_DMA:
		usdhi6_dma_check_error(host);
		break;
	case USDHI6_WAIT_FOR_STOP:
		usdhi6_write(host, USDHI6_SD_STOP, 0);
		if (host->io_error) {
			int ret = usdhi6_error_code(host);
			if (mrq->stop)
				mrq->stop->error = ret;
			else
				mrq->data->error = ret;
			dev_warn(mmc_dev(host->mmc), "%s(): %d\n", __func__, ret);
			break;
		}
		usdhi6_resp_cmd12(host);
		mrq->stop->error = 0;
		break;
	case USDHI6_WAIT_FOR_DATA_END:
		if (host->io_error) {
			mrq->data->error = usdhi6_error_code(host);
			dev_warn(mmc_dev(host->mmc), "%s(): %d\n", __func__,
				 mrq->data->error);
		}
		break;
	default:
		cmd->error = -EFAULT;
		dev_err(mmc_dev(host->mmc), "Invalid state %u\n", host->wait);
		usdhi6_request_done(host);
		return IRQ_HANDLED;
	}

	if (io_wait) {
		schedule_delayed_work(&host->timeout_work, host->timeout);

		if (!host->dma_active)
			usdhi6_wait_for_brwe(host, mrq->data->flags & MMC_DATA_READ);
		return IRQ_HANDLED;
	}

	if (!cmd->error) {
		if (data) {
			if (!data->error) {
				if (host->wait != USDHI6_WAIT_FOR_STOP &&
				    host->mrq->stop &&
				    !host->mrq->stop->error &&
				    !usdhi6_stop_cmd(host)) {

					usdhi6_wait_for_resp(host);

					schedule_delayed_work(&host->timeout_work,
							      host->timeout);

					return IRQ_HANDLED;
				}

				data->bytes_xfered = data->blocks * data->blksz;
			} else {

				dev_warn(mmc_dev(host->mmc), "%s(): data error %d\n",
					 __func__, data->error);
				usdhi6_sg_unmap(host, true);
			}
		} else if (cmd->opcode == MMC_APP_CMD) {
			host->app_cmd = true;
		}
	}

	usdhi6_request_done(host);

	return IRQ_HANDLED;
}
