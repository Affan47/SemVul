fast_pf_fix_direct_spte(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp,
			u64 *sptep, u64 spte)
{
	gfn_t gfn;

	WARN_ON(!sp->role.direct);


	gfn = kvm_mmu_page_get_gfn(sp, sptep - sp->spt);


	if (cmpxchg64(sptep, spte, spte | PT_WRITABLE_MASK) == spte)
		kvm_vcpu_mark_page_dirty(vcpu, gfn);

	return true;
}
