intel_gpio_probe(struct pci_dev *pdev,
			  const struct pci_device_id *id)
{
	void __iomem *base;
	struct intel_mid_gpio *priv;
	u32 gpio_base;
	u32 irq_base;
	int retval;
	struct intel_mid_gpio_ddata *ddata =
				(struct intel_mid_gpio_ddata *)id->driver_data;

	retval = pcim_enable_device(pdev);
	if (retval)
		return retval;

	retval = pcim_iomap_regions(pdev, 1 << 0 | 1 << 1, pci_name(pdev));
	if (retval) {
		dev_err(&pdev->dev, "I/O memory mapping error\n");
		return retval;
	}

	base = pcim_iomap_table(pdev)[1];

	irq_base = readl(base);
	gpio_base = readl(sizeof(u32) + base);


	pcim_iounmap_regions(pdev, 1 << 1);

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(&pdev->dev, "can't allocate chip data\n");
		return -ENOMEM;
	}

	priv->reg_base = pcim_iomap_table(pdev)[0];
	priv->chip.label = dev_name(&pdev->dev);
	priv->chip.dev = &pdev->dev;
	priv->chip.request = intel_gpio_request;
	priv->chip.direction_input = intel_gpio_direction_input;
	priv->chip.direction_output = intel_gpio_direction_output;
	priv->chip.get = intel_gpio_get;
	priv->chip.set = intel_gpio_set;
	priv->chip.base = gpio_base;
	priv->chip.ngpio = ddata->ngpio;
	priv->chip.can_sleep = false;
	priv->pdev = pdev;

	spin_lock_init(&priv->lock);

	pci_set_drvdata(pdev, priv);
	retval = gpiochip_add(&priv->chip);
	if (retval) {
		dev_err(&pdev->dev, "gpiochip_add error %d\n", retval);
		return retval;
	}

	retval = gpiochip_irqchip_add(&priv->chip,
				      &intel_mid_irqchip,
				      irq_base,
				      handle_simple_irq,
				      IRQ_TYPE_NONE);
	if (retval) {
		dev_err(&pdev->dev,
			"could not connect irqchip to gpiochip\n");
		return retval;
	}

	intel_mid_irq_init_hw(priv);

	gpiochip_set_chained_irqchip(&priv->chip,
				     &intel_mid_irqchip,
				     pdev->irq,
				     intel_mid_irq_handler);

	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_allow(&pdev->dev);

	return 0;
}
