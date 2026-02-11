tsi721_request_irq(struct rio_mport *mport)
{
	struct tsi721_device *priv = mport->priv;
	int err;

#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX)
		err = tsi721_request_msix(mport);
	else
#endif
		err = request_irq(priv->pdev->irq, tsi721_irqhandler,
			  (priv->flags & TSI721_USING_MSI) ? 0 : IRQF_SHARED,
			  DRV_NAME, (void *)mport);

	if (err)
		dev_err(&priv->pdev->dev,
			"Unable to allocate interrupt, Error: %d\n", err);

	return err;
}
