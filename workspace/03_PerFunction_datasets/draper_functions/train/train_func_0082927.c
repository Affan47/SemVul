wl12xx_sdio_power_off(struct wl12xx_sdio_glue *glue)
{
	int ret;
	struct sdio_func *func = dev_to_sdio_func(glue->dev);
	struct mmc_card *card = func->card;

	sdio_claim_host(func);
	sdio_disable_func(func);
	sdio_release_host(func);


	ret = mmc_power_save_host(card->host);
	if (ret < 0)
		goto out;


	pm_runtime_put_sync(&card->dev);

out:
	return ret;
}
