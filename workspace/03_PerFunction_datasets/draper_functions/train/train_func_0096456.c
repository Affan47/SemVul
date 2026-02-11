__set_gcr3(struct protection_domain *domain, int pasid,
		      unsigned long cr3)
{
	u64 *pte;

	if (domain->mode != PAGE_MODE_NONE)
		return -EINVAL;

	pte = __get_gcr3_pte(domain->gcr3_tbl, domain->glx, pasid, true);
	if (pte == NULL)
		return -ENOMEM;

	*pte = (cr3 & PAGE_MASK) | GCR3_VALID;

	return __amd_iommu_flush_tlb(domain, pasid);
}
