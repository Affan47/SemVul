lpass_platform_lpaif_irq(int irq, void *data)
{
	struct lpass_data *drvdata = data;
	struct lpass_variant *v = drvdata->variant;
	unsigned int irqs;
	int rv, chan;

	rv = regmap_read(drvdata->lpaif_map,
			LPAIF_IRQSTAT_REG(v, LPAIF_IRQ_PORT_HOST), &irqs);
	if (rv) {
		pr_err("%s() error reading from irqstat reg: %d\n",
				__func__, rv);
		return IRQ_NONE;
	}


	for (chan = 0; chan < LPASS_MAX_DMA_CHANNELS; chan++) {
		if (irqs & LPAIF_IRQ_ALL(chan) && drvdata->substream[chan]) {
			rv = lpass_dma_interrupt_handler(
						drvdata->substream[chan],
						drvdata, chan, irqs);
			if (rv != IRQ_HANDLED)
				return rv;
		}
	}

	return IRQ_HANDLED;
}
