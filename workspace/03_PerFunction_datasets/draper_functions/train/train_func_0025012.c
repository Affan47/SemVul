page_check_address_pmd(struct page *page,
			      struct mm_struct *mm,
			      unsigned long address,
			      enum page_check_address_pmd_flag flag,
			      spinlock_t **ptl)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;

	if (address & ~HPAGE_PMD_MASK)
		return NULL;

	pgd = pgd_offset(mm, address);
	if (!pgd_present(*pgd))
		return NULL;
	pud = pud_offset(pgd, address);
	if (!pud_present(*pud))
		return NULL;
	pmd = pmd_offset(pud, address);

	*ptl = pmd_lock(mm, pmd);
	if (!pmd_present(*pmd))
		goto unlock;
	if (pmd_page(*pmd) != page)
		goto unlock;


	if (flag == PAGE_CHECK_ADDRESS_PMD_NOTSPLITTING_FLAG &&
	    pmd_trans_splitting(*pmd))
		goto unlock;
	if (pmd_trans_huge(*pmd)) {
		VM_BUG_ON(flag == PAGE_CHECK_ADDRESS_PMD_SPLITTING_FLAG &&
			  !pmd_trans_splitting(*pmd));
		return pmd;
	}
unlock:
	spin_unlock(*ptl);
	return NULL;
}
