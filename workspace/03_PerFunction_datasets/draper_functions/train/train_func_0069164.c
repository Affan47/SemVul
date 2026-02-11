intel_irq(int irq, void *dev_id)
{
	struct intel_device *idev = dev_id;

	dev_info(&idev->pdev->dev, "hci_intel irq\n");

	mutex_lock(&idev->hu_lock);
	if (idev->hu)
		intel_lpm_host_wake(idev->hu);
	mutex_unlock(&idev->hu_lock);


	pm_runtime_get(&idev->pdev->dev);
	pm_runtime_mark_last_busy(&idev->pdev->dev);
	pm_runtime_put_autosuspend(&idev->pdev->dev);

	return IRQ_HANDLED;
}
