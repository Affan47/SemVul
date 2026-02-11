kvm_age_hva(struct kvm *kvm, unsigned long start, unsigned long end)
{


	if (!shadow_accessed_mask) {


		kvm->mmu_notifier_seq++;
		return kvm_handle_hva_range(kvm, start, end, 0,
					    kvm_unmap_rmapp);
	}

	return kvm_handle_hva_range(kvm, start, end, 0, kvm_age_rmapp);
}
