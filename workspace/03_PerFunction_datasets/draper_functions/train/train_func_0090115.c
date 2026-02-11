intel_iommu_get_pts(struct intel_iommu *iommu)
{


	if (ecap_pss(iommu->ecap) < 5)
		return 0;


	return find_first_bit((unsigned long *)&iommu->pasid_max,
			MAX_NR_PASID_BITS) - 5;
}
