bdc_probe(struct platform_device *pdev)
{
	struct bdc *bdc;
	struct resource *res;
	int ret = -ENOMEM;
	int irq;
	u32 temp;
	struct device *dev = &pdev->dev;

	dev_dbg(dev, "%s()\n", __func__);
	bdc = devm_kzalloc(dev, sizeof(*bdc), GFP_KERNEL);
	if (!bdc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	bdc->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(bdc->regs)) {
		dev_err(dev, "ioremap error\n");
		return -ENOMEM;
	}
	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "platform_get_irq failed:%d\n", irq);
		return irq;
	}
	spin_lock_init(&bdc->lock);
	platform_set_drvdata(pdev, bdc);
	bdc->irq = irq;
	bdc->dev = dev;
	dev_dbg(bdc->dev, "bdc->regs: %p irq=%d\n", bdc->regs, bdc->irq);

	temp = bdc_readl(bdc->regs, BDC_BDCSC);
	if ((temp & BDC_P64) &&
			!dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64))) {
		dev_dbg(bdc->dev, "Using 64-bit address\n");
	} else {
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (ret) {
			dev_err(bdc->dev, "No suitable DMA config available, abort\n");
			return -ENOTSUPP;
		}
		dev_dbg(bdc->dev, "Using 32-bit address\n");
	}
	ret = bdc_hw_init(bdc);
	if (ret) {
		dev_err(bdc->dev, "BDC init failure:%d\n", ret);
		return ret;
	}
	ret = bdc_udc_init(bdc);
	if (ret) {
		dev_err(bdc->dev, "BDC Gadget init failure:%d\n", ret);
		goto cleanup;
	}
	return 0;

cleanup:
	bdc_hw_exit(bdc);

	return ret;
}
