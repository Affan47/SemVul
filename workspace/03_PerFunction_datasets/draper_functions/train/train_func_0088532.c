assign_guest_irq(struct kvm *kvm,
			    struct kvm_assigned_dev_kernel *dev,
			    struct kvm_assigned_irq *irq,
			    unsigned long guest_irq_type)
{
	int id;
	int r = -EEXIST;

	if (dev->irq_requested_type & KVM_DEV_IRQ_GUEST_MASK)
		return r;

	id = kvm_request_irq_source_id(kvm);
	if (id < 0)
		return id;

	dev->irq_source_id = id;

	switch (guest_irq_type) {
	case KVM_DEV_IRQ_GUEST_INTX:
		r = assigned_device_enable_guest_intx(kvm, dev, irq);
		break;
	case KVM_DEV_IRQ_GUEST_MSI:
		r = assigned_device_enable_guest_msi(kvm, dev, irq);
		break;
	case KVM_DEV_IRQ_GUEST_MSIX:
		r = assigned_device_enable_guest_msix(kvm, dev, irq);
		break;
	default:
		r = -EINVAL;
	}

	if (!r) {
		dev->irq_requested_type |= guest_irq_type;
		if (dev->ack_notifier.gsi != -1)
			kvm_register_irq_ack_notifier(kvm, &dev->ack_notifier);
	} else {
		kvm_free_irq_source_id(kvm, dev->irq_source_id);
		dev->irq_source_id = -1;
	}

	return r;
}
