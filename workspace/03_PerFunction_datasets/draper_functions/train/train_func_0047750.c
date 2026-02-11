intel_punit_ipc_probe(struct platform_device *pdev)
{
	int irq, ret;

	punit_ipcdev = devm_kzalloc(&pdev->dev,
				    sizeof(*punit_ipcdev), GFP_KERNEL);
	if (!punit_ipcdev)
		return -ENOMEM;

	platform_set_drvdata(pdev, punit_ipcdev);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		punit_ipcdev->irq = 0;
		dev_warn(&pdev->dev, "Invalid IRQ, using polling mode\n");
	} else {
		ret = devm_request_irq(&pdev->dev, irq, intel_punit_ioc,
				       IRQF_NO_SUSPEND, "intel_punit_ipc",
				       &punit_ipcdev);
		if (ret) {
			dev_err(&pdev->dev, "Failed to request irq: %d\n", irq);
			return ret;
		}
		punit_ipcdev->irq = irq;
	}

	ret = intel_punit_get_bars(pdev);
	if (ret)
		goto out;

	punit_ipcdev->dev = &pdev->dev;
	mutex_init(&punit_ipcdev->lock);
	init_completion(&punit_ipcdev->cmd_complete);

out:
	return ret;
}
