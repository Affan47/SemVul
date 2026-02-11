post_set(void) __releases(set_atomicity_lock)
{

	count_vm_tlb_event(NR_TLB_LOCAL_FLUSH_ALL);
	__flush_tlb();


	mtrr_wrmsr(MSR_MTRRdefType, deftype_lo, deftype_hi);


	write_cr0(read_cr0() & ~X86_CR0_CD);


	if (cpu_has_pge)
		__write_cr4(cr4);
	raw_spin_unlock(&set_atomicity_lock);
}
