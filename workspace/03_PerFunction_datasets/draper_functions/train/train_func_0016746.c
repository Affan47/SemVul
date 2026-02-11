kvm_request_irq_source_id(struct kvm *kvm)
{
	unsigned long *bitmap = &kvm->arch.irq_sources_bitmap;
	int irq_source_id;

	mutex_lock(&kvm->irq_lock);
	irq_source_id = find_first_zero_bit(bitmap, BITS_PER_LONG);

	if (irq_source_id >= BITS_PER_LONG) {
		printk(KERN_WARNING "kvm: exhaust allocatable IRQ sources!\n");
		irq_source_id = -EFAULT;
		goto unlock;
	}

	ASSERT(irq_source_id != KVM_USERSPACE_IRQ_SOURCE_ID);
	ASSERT(irq_source_id != KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID);
	set_bit(irq_source_id, bitmap);
unlock:
	mutex_unlock(&kvm->irq_lock);

	return irq_source_id;
}
