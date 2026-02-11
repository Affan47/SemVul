ath6kl_sdio_irq_enable(struct ath6kl *ar)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	int ret;

	sdio_claim_host(ar_sdio->func);


	ret =  sdio_claim_irq(ar_sdio->func, ath6kl_sdio_irq_handler);
	if (ret)
		ath6kl_err("Failed to claim sdio irq: %d\n", ret);

	sdio_release_host(ar_sdio->func);
}
