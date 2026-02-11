whcrc_irq_cb(int irq, void *_whcrc)
{
	struct whcrc *whcrc = _whcrc;
	struct device *dev = &whcrc->umc_dev->dev;
	u32 urcsts;

	urcsts = le_readl(whcrc->rc_base + URCSTS);
	if (!(urcsts & URCSTS_INT_MASK))
		return IRQ_NONE;
	le_writel(urcsts & URCSTS_INT_MASK, whcrc->rc_base + URCSTS);

	if (urcsts & URCSTS_HSE) {
		dev_err(dev, "host system error -- hardware halted\n");

		goto out;
	}
	if (urcsts & URCSTS_ER)
		schedule_work(&whcrc->event_work);
	if (urcsts & URCSTS_RCI)
		wake_up_all(&whcrc->cmd_wq);
out:
	return IRQ_HANDLED;
}
