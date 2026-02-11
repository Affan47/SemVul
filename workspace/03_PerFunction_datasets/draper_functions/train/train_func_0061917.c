reset_tdp_shadow_zero_bits_mask(struct kvm_vcpu *vcpu,
				struct kvm_mmu *context)
{
	if (boot_cpu_is_amd())
		__reset_rsvds_bits_mask(vcpu, &context->shadow_zero_check,
					boot_cpu_data.x86_phys_bits,
					context->shadow_root_level, false,
					cpu_has_gbpages, true, true);
	else
		__reset_rsvds_bits_mask_ept(&context->shadow_zero_check,
					    boot_cpu_data.x86_phys_bits,
					    false);

}
