sdio_single_irq_set(struct mmc_card *card)
{
	struct sdio_func *func;
	int i;

	card->sdio_single_irq = NULL;
	if ((card->host->caps & MMC_CAP_SDIO_IRQ) &&
	    card->host->sdio_irqs == 1)
		for (i = 0; i < card->sdio_funcs; i++) {
		       func = card->sdio_func[i];
		       if (func && func->irq_handler) {
			       card->sdio_single_irq = func;
			       break;
		       }
	       }
}
