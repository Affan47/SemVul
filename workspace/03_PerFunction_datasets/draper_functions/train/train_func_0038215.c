reset_shadow_zero_bits_mask(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
{
	bool uses_nx = context->nx || context->base_role.smep_andnot_wp;


	__reset_rsvds_bits_mask(vcpu, &context->shadow_zero_check,
				boot_cpu_data.x86_phys_bits,
				context->shadow_root_level, uses_nx,
				guest_cpuid_has_gbpages(vcpu), is_pse(vcpu),
				true);
}
