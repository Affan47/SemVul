sp_probe(struct platform_device *pdev)
{
	int err, irq = 0;
	void __iomem *addr;
	struct net_device *dev;
	struct sja1000_priv *priv;
	struct resource *res_mem, *res_irq = NULL;
	struct sja1000_platform_data *pdata;
	struct device_node *of = pdev->dev.of_node;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata && !of) {
		dev_err(&pdev->dev, "No platform data provided!\n");
		return -ENODEV;
	}

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res_mem)
		return -ENODEV;

	if (!devm_request_mem_region(&pdev->dev, res_mem->start,
				     resource_size(res_mem), DRV_NAME))
		return -EBUSY;

	addr = devm_ioremap_nocache(&pdev->dev, res_mem->start,
				    resource_size(res_mem));
	if (!addr)
		return -ENOMEM;

	if (of)
		irq = irq_of_parse_and_map(of, 0);
	else
		res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);

	if (!irq && !res_irq)
		return -ENODEV;

	dev = alloc_sja1000dev(0);
	if (!dev)
		return -ENOMEM;
	priv = netdev_priv(dev);

	if (res_irq) {
		irq = res_irq->start;
		priv->irq_flags = res_irq->flags & IRQF_TRIGGER_MASK;
		if (res_irq->flags & IORESOURCE_IRQ_SHAREABLE)
			priv->irq_flags |= IRQF_SHARED;
	} else {
		priv->irq_flags = IRQF_SHARED;
	}

	dev->irq = irq;
	priv->reg_base = addr;

	if (of)
		sp_populate_of(priv, of);
	else
		sp_populate(priv, pdata, res_mem->flags);

	platform_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = register_sja1000dev(dev);
	if (err) {
		dev_err(&pdev->dev, "registering %s failed (err=%d)\n",
			DRV_NAME, err);
		goto exit_free;
	}

	dev_info(&pdev->dev, "%s device registered (reg_base=%p, irq=%d)\n",
		 DRV_NAME, priv->reg_base, dev->irq);
	return 0;

 exit_free:
	free_sja1000dev(dev);
	return err;
}
