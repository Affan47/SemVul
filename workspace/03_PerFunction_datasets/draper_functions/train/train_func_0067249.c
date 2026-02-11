kvm_arch_mmu_enable_log_dirty_pt_masked(struct kvm *kvm,
				struct kvm_memory_slot *slot,
				gfn_t gfn_offset, unsigned long mask)
{
	if (kvm_x86_ops->enable_log_dirty_pt_masked)
		kvm_x86_ops->enable_log_dirty_pt_masked(kvm, slot, gfn_offset,
				mask);
	else
		kvm_mmu_write_protect_pt_masked(kvm, slot, gfn_offset, mask);
}
