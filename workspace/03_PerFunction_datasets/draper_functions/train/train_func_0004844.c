efi_call_phys_prolog(void)
{
	unsigned long vaddress;
	pgd_t *save_pgd;

	int pgd;
	int n_pgds;

	if (!efi_enabled(EFI_OLD_MEMMAP))
		return NULL;

	early_code_mapping_set_exec(1);

	n_pgds = DIV_ROUND_UP((max_pfn << PAGE_SHIFT), PGDIR_SIZE);
	save_pgd = kmalloc(n_pgds * sizeof(pgd_t), GFP_KERNEL);

	for (pgd = 0; pgd < n_pgds; pgd++) {
		save_pgd[pgd] = *pgd_offset_k(pgd * PGDIR_SIZE);
		vaddress = (unsigned long)__va(pgd * PGDIR_SIZE);
		set_pgd(pgd_offset_k(pgd * PGDIR_SIZE), *pgd_offset_k(vaddress));
	}
	__flush_tlb_all();

	return save_pgd;
}
