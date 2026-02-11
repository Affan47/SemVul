kgd_set_pasid_vmid_mapping(struct kgd_dev *kgd, unsigned int pasid,
					unsigned int vmid)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);


	uint32_t pasid_mapping = (pasid == 0) ? 0 : (uint32_t)pasid |
			ATC_VMID0_PASID_MAPPING__VALID_MASK;

	WREG32(mmATC_VMID0_PASID_MAPPING + vmid, pasid_mapping);

	while (!(RREG32(mmATC_VMID_PASID_MAPPING_UPDATE_STATUS) & (1U << vmid)))
		cpu_relax();
	WREG32(mmATC_VMID_PASID_MAPPING_UPDATE_STATUS, 1U << vmid);


	WREG32(mmIH_VMID_0_LUT + vmid, pasid_mapping);

	return 0;
}
