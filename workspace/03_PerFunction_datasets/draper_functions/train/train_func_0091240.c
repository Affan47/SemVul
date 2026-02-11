__flush_pasid(struct protection_domain *domain, int pasid,
			 u64 address, bool size)
{
	struct iommu_dev_data *dev_data;
	struct iommu_cmd cmd;
	int i, ret;

	if (!(domain->flags & PD_IOMMUV2_MASK))
		return -EINVAL;

	build_inv_iommu_pasid(&cmd, domain->id, pasid, address, size);


	for (i = 0; i < amd_iommus_present; ++i) {
		if (domain->dev_iommu[i] == 0)
			continue;

		ret = iommu_queue_command(amd_iommus[i], &cmd);
		if (ret != 0)
			goto out;
	}


	domain_flush_complete(domain);


	list_for_each_entry(dev_data, &domain->dev_list, list) {
		struct amd_iommu *iommu;
		int qdep;


		if (!dev_data->ats.enabled)
			continue;

		qdep  = dev_data->ats.qdep;
		iommu = amd_iommu_rlookup_table[dev_data->devid];

		build_inv_iotlb_pasid(&cmd, dev_data->devid, pasid,
				      qdep, address, size);

		ret = iommu_queue_command(iommu, &cmd);
		if (ret != 0)
			goto out;
	}


	domain_flush_complete(domain);

	ret = 0;

out:

	return ret;
}
