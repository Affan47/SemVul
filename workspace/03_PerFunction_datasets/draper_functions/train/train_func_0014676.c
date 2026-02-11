pch_gpio_suspend(struct pci_dev *pdev, pm_message_t state)
{
	s32 ret;
	struct pch_gpio *chip = pci_get_drvdata(pdev);
	unsigned long flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	pch_gpio_save_reg_conf(chip);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	ret = pci_save_state(pdev);
	if (ret) {
		dev_err(&pdev->dev, "pci_save_state Failed-%d\n", ret);
		return ret;
	}
	pci_disable_device(pdev);
	pci_set_power_state(pdev, PCI_D0);
	ret = pci_enable_wake(pdev, PCI_D0, 1);
	if (ret)
		dev_err(&pdev->dev, "pci_enable_wake Failed -%d\n", ret);

	return 0;
}
