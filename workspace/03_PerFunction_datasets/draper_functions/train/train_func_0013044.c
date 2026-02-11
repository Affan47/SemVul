kvm_cpu_has_extint(struct kvm_vcpu *v)
{
	u8 accept = kvm_apic_accept_pic_intr(v);

	if (accept) {
		if (irqchip_split(v->kvm))
			return pending_userspace_extint(v);
		else
			return pic_irqchip(v->kvm)->output;
	} else
		return 0;
}
