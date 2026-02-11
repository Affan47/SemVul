xen_load_gdt(const struct desc_ptr *dtr)
{
	unsigned long va = dtr->address;
	unsigned int size = dtr->size + 1;
	unsigned pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
	unsigned long frames[pages];
	int f;


	BUG_ON(size > 65536);
	BUG_ON(va & ~PAGE_MASK);

	for (f = 0; va < dtr->address + size; va += PAGE_SIZE, f++) {
		int level;
		pte_t *ptep;
		unsigned long pfn, mfn;
		void *virt;


		ptep = lookup_address(va, &level);
		BUG_ON(ptep == NULL);

		pfn = pte_pfn(*ptep);
		mfn = pfn_to_mfn(pfn);
		virt = __va(PFN_PHYS(pfn));

		frames[f] = mfn;

		make_lowmem_page_readonly((void *)va);
		make_lowmem_page_readonly(virt);
	}

	if (HYPERVISOR_set_gdt(frames, size / sizeof(struct desc_struct)))
		BUG();
}
