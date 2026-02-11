remove_pagetable(unsigned long start, unsigned long end, bool direct)
{
	unsigned long next;
	unsigned long addr;
	pgd_t *pgd;
	pud_t *pud;
	bool pgd_changed = false;

	for (addr = start; addr < end; addr = next) {
		next = pgd_addr_end(addr, end);

		pgd = pgd_offset_k(addr);
		if (!pgd_present(*pgd))
			continue;

		pud = (pud_t *)pgd_page_vaddr(*pgd);
		remove_pud_table(pud, addr, next, direct);
		if (free_pud_table(pud, pgd))
			pgd_changed = true;
	}

	if (pgd_changed)
		sync_global_pgds(start, end - 1, 1);

	flush_tlb_all();
}
