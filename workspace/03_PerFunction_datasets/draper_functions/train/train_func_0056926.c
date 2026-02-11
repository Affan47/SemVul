xgene_dma_get_resources(struct platform_device *pdev,
				   struct xgene_dma *pdma)
{
	struct resource *res;
	int irq, i;


	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get csr region\n");
		return -ENXIO;
	}

	pdma->csr_dma = devm_ioremap(&pdev->dev, res->start,
				     resource_size(res));
	if (!pdma->csr_dma) {
		dev_err(&pdev->dev, "Failed to ioremap csr region");
		return -ENOMEM;
	}


	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get ring csr region\n");
		return -ENXIO;
	}

	pdma->csr_ring =  devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	if (!pdma->csr_ring) {
		dev_err(&pdev->dev, "Failed to ioremap ring csr region");
		return -ENOMEM;
	}


	res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get ring cmd csr region\n");
		return -ENXIO;
	}

	pdma->csr_ring_cmd = devm_ioremap(&pdev->dev, res->start,
					  resource_size(res));
	if (!pdma->csr_ring_cmd) {
		dev_err(&pdev->dev, "Failed to ioremap ring cmd csr region");
		return -ENOMEM;
	}

	pdma->csr_ring_cmd += XGENE_DMA_RING_CMD_SM_OFFSET;


	res = platform_get_resource(pdev, IORESOURCE_MEM, 3);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get efuse csr region\n");
		return -ENXIO;
	}

	pdma->csr_efuse = devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	if (!pdma->csr_efuse) {
		dev_err(&pdev->dev, "Failed to ioremap efuse csr region");
		return -ENOMEM;
	}


	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev, "Failed to get Error IRQ\n");
		return -ENXIO;
	}

	pdma->err_irq = irq;


	for (i = 1; i <= XGENE_DMA_MAX_CHANNEL; i++) {
		irq = platform_get_irq(pdev, i);
		if (irq <= 0) {
			dev_err(&pdev->dev, "Failed to get Rx IRQ\n");
			return -ENXIO;
		}

		pdma->chan[i - 1].rx_irq = irq;
	}

	return 0;
}
