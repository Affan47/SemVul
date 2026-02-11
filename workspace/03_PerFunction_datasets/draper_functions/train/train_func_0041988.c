if_sdio_exit_deep_sleep(struct lbs_private *priv)
{
	struct if_sdio_card *card = priv->card;
	int ret = -1;

	lbs_deb_enter(LBS_DEB_SDIO);
	sdio_claim_host(card->func);

	sdio_writeb(card->func, HOST_POWER_UP, CONFIGURATION_REG, &ret);
	if (ret)
		netdev_err(priv->dev, "sdio_writeb failed!\n");

	sdio_release_host(card->func);
	lbs_deb_leave_args(LBS_DEB_SDIO, "ret %d", ret);
	return ret;
}
