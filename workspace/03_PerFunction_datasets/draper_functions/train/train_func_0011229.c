cciss_request_irq(ctlr_info_t *h,
	irqreturn_t (*msixhandler)(int, void *),
	irqreturn_t (*intxhandler)(int, void *))
{
	if (h->msix_vector || h->msi_vector) {
		if (!request_irq(h->intr[h->intr_mode], msixhandler,
				0, h->devname, h))
			return 0;
		dev_err(&h->pdev->dev, "Unable to get msi irq %d"
			" for %s\n", h->intr[h->intr_mode],
			h->devname);
		return -1;
	}

	if (!request_irq(h->intr[h->intr_mode], intxhandler,
			IRQF_SHARED, h->devname, h))
		return 0;
	dev_err(&h->pdev->dev, "Unable to get irq %d for %s\n",
		h->intr[h->intr_mode], h->devname);
	return -1;
}
