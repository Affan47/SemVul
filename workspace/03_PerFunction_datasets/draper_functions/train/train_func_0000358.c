tifm_sd_end_cmd(unsigned long data)
{
	struct tifm_sd *host = (struct tifm_sd*)data;
	struct tifm_dev *sock = host->dev;
	struct mmc_host *mmc = tifm_get_drvdata(sock);
	struct mmc_request *mrq;
	struct mmc_data *r_data = NULL;
	unsigned long flags;

	spin_lock_irqsave(&sock->lock, flags);

	del_timer(&host->timer);
	mrq = host->req;
	host->req = NULL;

	if (!mrq) {
		pr_err(" %s : no request to complete?\n",
		       dev_name(&sock->dev));
		spin_unlock_irqrestore(&sock->lock, flags);
		return;
	}

	r_data = mrq->cmd->data;
	if (r_data) {
		if (host->no_dma) {
			writel((~TIFM_MMCSD_BUFINT)
			       & readl(sock->addr + SOCK_MMCSD_INT_ENABLE),
			       sock->addr + SOCK_MMCSD_INT_ENABLE);
		} else {
			tifm_unmap_sg(sock, &host->bounce_buf, 1,
				      (r_data->flags & MMC_DATA_WRITE)
				      ? PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);
			tifm_unmap_sg(sock, r_data->sg, r_data->sg_len,
				      (r_data->flags & MMC_DATA_WRITE)
				      ? PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);
		}

		r_data->bytes_xfered = r_data->blocks
			- readl(sock->addr + SOCK_MMCSD_NUM_BLOCKS) - 1;
		r_data->bytes_xfered *= r_data->blksz;
		r_data->bytes_xfered += r_data->blksz
			- readl(sock->addr + SOCK_MMCSD_BLOCK_LEN) + 1;
	}

	writel((~TIFM_CTRL_LED) & readl(sock->addr + SOCK_CONTROL),
	       sock->addr + SOCK_CONTROL);

	spin_unlock_irqrestore(&sock->lock, flags);
	mmc_request_done(mmc, mrq);
}
