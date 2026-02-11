if_sdio_finish_power_on(struct if_sdio_card *card)
{
	struct sdio_func *func = card->func;
	struct lbs_private *priv = card->priv;
	int ret;

	sdio_claim_host(func);
	sdio_set_block_size(card->func, IF_SDIO_BLOCK_SIZE);


	if ((card->model != MODEL_8385)
			&& (card->model != MODEL_8686))
		card->rx_unit = if_sdio_read_rx_unit(card);
	else
		card->rx_unit = 0;


	ret = sdio_claim_irq(func, if_sdio_interrupt);
	if (ret)
		goto release;


	sdio_writeb(func, 0x0f, IF_SDIO_H_INT_MASK, &ret);
	if (ret)
		goto release_irq;

	sdio_release_host(func);


	priv->fw_ready = 1;


	if (card->model == MODEL_8688) {
		struct cmd_header cmd;

		memset(&cmd, 0, sizeof(cmd));

		lbs_deb_sdio("send function INIT command\n");
		if (__lbs_cmd(priv, CMD_FUNC_INIT, &cmd, sizeof(cmd),
				lbs_cmd_copyback, (unsigned long) &cmd))
			netdev_alert(priv->dev, "CMD_FUNC_INIT cmd failed\n");
	}

	wake_up(&card->pwron_waitq);

	if (!card->started) {
		ret = lbs_start_card(priv);
		if_sdio_power_off(card);
		if (ret == 0) {
			card->started = true;


			pm_runtime_put(&func->dev);
		}
	}

	return;

release_irq:
	sdio_release_irq(func);
release:
	sdio_release_host(func);
}
