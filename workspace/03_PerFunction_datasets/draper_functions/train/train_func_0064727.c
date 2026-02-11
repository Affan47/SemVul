mm_alloc_pmd(struct mm_struct *mm, unsigned long address)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd = NULL;

	pgd = pgd_offset(mm, address);
	pud = pud_alloc(mm, pgd, address);
	if (pud)


		pmd = pmd_alloc(mm, pud, address);
	return pmd;
}
