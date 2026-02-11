ssp_remove(struct spi_device *spi)
{
	struct ssp_data *data = spi_get_drvdata(spi);

	if (ssp_command(data, SSP_MSG2SSP_AP_STATUS_SHUTDOWN, 0) < 0)
		dev_err(&data->spi->dev,
			"SSP_MSG2SSP_AP_STATUS_SHUTDOWN failed\n");

	ssp_enable_mcu(data, false);
	ssp_disable_wdt_timer(data);

	ssp_clean_pending_list(data);

	free_irq(data->spi->irq, data);

	del_timer_sync(&data->wdt_timer);
	cancel_work_sync(&data->work_wdt);

	mutex_destroy(&data->comm_lock);
	mutex_destroy(&data->pending_lock);

	mfd_remove_devices(&spi->dev);

	return 0;
}
