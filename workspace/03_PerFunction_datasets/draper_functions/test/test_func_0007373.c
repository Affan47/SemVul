kvm_init_shadow_mmu(struct kvm_vcpu *vcpu)
{
	bool smep = kvm_read_cr4_bits(vcpu, X86_CR4_SMEP);
	bool smap = kvm_read_cr4_bits(vcpu, X86_CR4_SMAP);
	struct kvm_mmu *context = &vcpu->arch.mmu;

	MMU_WARN_ON(VALID_PAGE(context->root_hpa));

	if (!is_paging(vcpu))
		nonpaging_init_context(vcpu, context);
	else if (is_long_mode(vcpu))
		paging64_init_context(vcpu, context);
	else if (is_pae(vcpu))
		paging32E_init_context(vcpu, context);
	else
		paging32_init_context(vcpu, context);

	context->base_role.nxe = is_nx(vcpu);
	context->base_role.cr4_pae = !!is_pae(vcpu);
	context->base_role.cr0_wp  = is_write_protection(vcpu);
	context->base_role.smep_andnot_wp
		= smep && !is_write_protection(vcpu);
	context->base_role.smap_andnot_wp
		= smap && !is_write_protection(vcpu);
	context->base_role.smm = is_smm(vcpu);
	reset_shadow_zero_bits_mask(vcpu, context);
}
