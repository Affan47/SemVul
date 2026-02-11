__clear_gcr3(struct protection_domain *domain, int pasid)
{
	u64 *pte;

	if (domain->mode != PAGE_MODE_NONE)
		return -EINVAL;

	pte = __get_gcr3_pte(domain->gcr3_tbl, domain->glx, pasid, false);
	if (pte == NULL)
		return 0;

	*pte = 0;

	return __amd_iommu_flush_tlb(domain, pasid);
}
