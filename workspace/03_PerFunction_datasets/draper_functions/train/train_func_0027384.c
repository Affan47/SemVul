kvm_set_irq_inatomic(struct kvm *kvm, int irq_source_id, u32 irq,
				int level)
{
	struct kvm_kernel_irq_routing_entry entries[KVM_NR_IRQCHIPS];
	struct kvm_kernel_irq_routing_entry *e;
	int ret = -EINVAL;
	int idx;

	trace_kvm_set_irq(irq, level, irq_source_id);


	idx = srcu_read_lock(&kvm->irq_srcu);
	if (kvm_irq_map_gsi(kvm, entries, irq) > 0) {
		e = &entries[0];
		ret = kvm_arch_set_irq_inatomic(e, kvm, irq_source_id,
						irq, level);
	}
	srcu_read_unlock(&kvm->irq_srcu, idx);
	return ret;
}
