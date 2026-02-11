x86_64_xen_kdump_load_page(ulong kvaddr, char *pgbuf)
{
	ulong mfn;
	ulong *pml4, *pgd, *pmd, *ptep;

        pml4 = ((ulong *)machdep->machspec->pml4) + pml4_index(kvaddr);
	mfn = ((*pml4) & PHYSICAL_PAGE_MASK) >> PAGESHIFT();

	if (CRASHDEBUG(3))
		fprintf(fp,
		    "[%lx] pml4: %lx  mfn: %lx  pml4_index: %lx\n",
			kvaddr, *pml4, mfn, pml4_index(kvaddr));

        if (!readmem(PTOB(mfn), PHYSADDR, machdep->pgd, PAGESIZE(),
            "xen kdump pud page", RETURN_ON_ERROR))
		error(FATAL, "cannot read/find pud page\n");

	machdep->last_pgd_read = mfn;

        if (CRASHDEBUG(7))
		x86_64_debug_dump_page(fp, machdep->pgd,
                	"contents of page upper directory page:");

        pgd = ((ulong *)machdep->pgd) + pgd_index(kvaddr);
	mfn = ((*pgd) & PHYSICAL_PAGE_MASK) >> PAGESHIFT();

	if (CRASHDEBUG(3))
		fprintf(fp,
		    "[%lx] pgd: %lx  mfn: %lx  pgd_index: %lx\n",
			kvaddr, *pgd, mfn, pgd_index(kvaddr));

	if (!readmem(PTOB(mfn), PHYSADDR, machdep->pmd, PAGESIZE(),
            "xen kdump pmd page", RETURN_ON_ERROR))
                error(FATAL, "cannot read/find pmd page\n");

	machdep->last_pmd_read = mfn;

        if (CRASHDEBUG(7))
		x86_64_debug_dump_page(fp, machdep->pmd,
			"contents of page middle directory page:");

        pmd = ((ulong *)machdep->pmd) + pmd_index(kvaddr);
	mfn = ((*pmd) & PHYSICAL_PAGE_MASK) >> PAGESHIFT();

	if (CRASHDEBUG(3))
		fprintf(fp,
		    "[%lx] pmd: %lx  mfn: %lx  pmd_index: %lx\n",
			kvaddr, *pmd, mfn, pmd_index(kvaddr));

       if (!readmem(PTOB(mfn), PHYSADDR, machdep->ptbl, PAGESIZE(),
            "xen kdump page table page", RETURN_ON_ERROR))
                error(FATAL, "cannot read/find page table page\n");

	machdep->last_ptbl_read = mfn;

        if (CRASHDEBUG(7))
		x86_64_debug_dump_page(fp, machdep->ptbl,
			"contents of page table page:");

        ptep = ((ulong *)machdep->ptbl) + pte_index(kvaddr);
	mfn = ((*ptep) & PHYSICAL_PAGE_MASK) >> PAGESHIFT();

	if (CRASHDEBUG(3))
		fprintf(fp,
		    "[%lx] ptep: %lx  mfn: %lx  pte_index: %lx\n",
			kvaddr, *ptep, mfn, pte_index(kvaddr));

       if (!readmem(PTOB(mfn), PHYSADDR, pgbuf, PAGESIZE(),
            "xen kdump page table page", RETURN_ON_ERROR))
                error(FATAL, "cannot read/find pte page\n");

        if (CRASHDEBUG(7))
		x86_64_debug_dump_page(fp, pgbuf,
			"contents of page:");

	return pgbuf;
}
