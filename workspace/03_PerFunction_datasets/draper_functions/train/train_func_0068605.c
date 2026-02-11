remove_pte_table(pte_t *pte_start, unsigned long addr, unsigned long end,
		 bool direct)
{
	unsigned long next, pages = 0;
	pte_t *pte;
	void *page_addr;
	phys_addr_t phys_addr;

	pte = pte_start + pte_index(addr);
	for (; addr < end; addr = next, pte++) {
		next = (addr + PAGE_SIZE) & PAGE_MASK;
		if (next > end)
			next = end;

		if (!pte_present(*pte))
			continue;


		phys_addr = pte_val(*pte) + (addr & PAGE_MASK);
		if (phys_addr < (phys_addr_t)0x40000000)
			return;

		if (IS_ALIGNED(addr, PAGE_SIZE) &&
		    IS_ALIGNED(next, PAGE_SIZE)) {


			if (!direct)
				free_pagetable(pte_page(*pte), 0);

			spin_lock(&init_mm.page_table_lock);
			pte_clear(&init_mm, addr, pte);
			spin_unlock(&init_mm.page_table_lock);


			pages++;
		} else {


			memset((void *)addr, PAGE_INUSE, next - addr);

			page_addr = page_address(pte_page(*pte));
			if (!memchr_inv(page_addr, PAGE_INUSE, PAGE_SIZE)) {
				free_pagetable(pte_page(*pte), 0);

				spin_lock(&init_mm.page_table_lock);
				pte_clear(&init_mm, addr, pte);
				spin_unlock(&init_mm.page_table_lock);
			}
		}
	}


	flush_tlb_all();
	if (direct)
		update_page_count(PG_LEVEL_4K, -pages);
}
