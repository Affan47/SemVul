sdv_gpio_probe(struct pci_dev *pdev,
					const struct pci_device_id *pci_id)
{
	struct sdv_gpio_chip_data *sd;
	unsigned long addr;
	const void *prop;
	int len;
	int ret;
	u32 mux_val;

	sd = kzalloc(sizeof(struct sdv_gpio_chip_data), GFP_KERNEL);
	if (!sd)
		return -ENOMEM;
	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(&pdev->dev, "can't enable device.\n");
		goto done;
	}

	ret = pci_request_region(pdev, GPIO_BAR, DRV_NAME);
	if (ret) {
		dev_err(&pdev->dev, "can't alloc PCI BAR #%d\n", GPIO_BAR);
		goto disable_pci;
	}

	addr = pci_resource_start(pdev, GPIO_BAR);
	if (!addr) {
		ret = -ENODEV;
		goto release_reg;
	}
	sd->gpio_pub_base = ioremap(addr, pci_resource_len(pdev, GPIO_BAR));

	prop = of_get_property(pdev->dev.of_node, "intel,muxctl", &len);
	if (prop && len == 4) {
		mux_val = of_read_number(prop, 1);
		writel(mux_val, sd->gpio_pub_base + GPMUXCTL);
	}

	ret = bgpio_init(&sd->bgpio, &pdev->dev, 4,
			sd->gpio_pub_base + GPINR, sd->gpio_pub_base + GPOUTR,
			NULL, sd->gpio_pub_base + GPOER, NULL, 0);
	if (ret)
		goto unmap;
	sd->bgpio.gc.ngpio = SDV_NUM_PUB_GPIOS;

	ret = gpiochip_add(&sd->bgpio.gc);
	if (ret < 0) {
		dev_err(&pdev->dev, "gpiochip_add() failed.\n");
		goto unmap;
	}

	ret = sdv_register_irqsupport(sd, pdev);
	if (ret)
		goto unmap;

	pci_set_drvdata(pdev, sd);
	dev_info(&pdev->dev, "Sodaville GPIO driver registered.\n");
	return 0;

unmap:
	iounmap(sd->gpio_pub_base);
release_reg:
	pci_release_region(pdev, GPIO_BAR);
disable_pci:
	pci_disable_device(pdev);
done:
	kfree(sd);
	return ret;
}
