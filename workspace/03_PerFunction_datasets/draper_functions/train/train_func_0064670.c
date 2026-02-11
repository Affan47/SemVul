kvm_assigned_dev_intx(int irq, void *dev_id)
{
	struct kvm_assigned_dev_kernel *assigned_dev = dev_id;
	int ret;

	spin_lock(&assigned_dev->intx_lock);
	if (pci_check_and_mask_intx(assigned_dev->dev)) {
		assigned_dev->host_irq_disabled = true;
		ret = IRQ_WAKE_THREAD;
	} else
		ret = IRQ_NONE;
	spin_unlock(&assigned_dev->intx_lock);

	return ret;
}
