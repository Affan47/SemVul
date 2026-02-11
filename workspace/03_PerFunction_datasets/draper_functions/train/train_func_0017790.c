toshsd_data_end_irq(struct toshsd_host *host)
{
	struct mmc_data *data = host->data;

	host->data = NULL;

	if (!data) {
		dev_warn(&host->pdev->dev, "Spurious data end IRQ\n");
		return;
	}

	if (data->error == 0)
		data->bytes_xfered = data->blocks * data->blksz;
	else
		data->bytes_xfered = 0;

	dev_dbg(&host->pdev->dev, "Completed data request xfr=%d\n",
		data->bytes_xfered);

	iowrite16(0, host->ioaddr + SD_STOPINTERNAL);

	toshsd_finish_request(host);
}
