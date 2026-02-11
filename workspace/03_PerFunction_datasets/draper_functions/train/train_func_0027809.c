pmdp_splitting_flush(struct vm_area_struct *vma,
			  unsigned long address, pmd_t *pmdp)
{
	int set;
	VM_BUG_ON(address & ~HPAGE_PMD_MASK);
	set = !test_and_set_bit(_PAGE_BIT_SPLITTING,
				(unsigned long *)pmdp);
	if (set) {
		pmd_update(vma->vm_mm, address, pmdp);

		flush_tlb_range(vma, address, address + HPAGE_PMD_SIZE);
	}
}
