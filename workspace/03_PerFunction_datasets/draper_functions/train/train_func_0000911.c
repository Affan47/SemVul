at86rf230_irq_status(void *context)
{
	struct at86rf230_state_change *ctx = context;
	struct at86rf230_local *lp = ctx->lp;
	const u8 *buf = ctx->buf;
	u8 irq = buf[1];

	enable_irq(lp->spi->irq);

	if (irq & IRQ_TRX_END) {
		at86rf230_irq_trx_end(ctx);
	} else {
		dev_err(&lp->spi->dev, "not supported irq %02x received\n",
			irq);
		kfree(ctx);
	}
}
