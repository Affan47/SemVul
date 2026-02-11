amdgpu_cgs_query_system_info(void *cgs_device,
				struct cgs_system_info *sys_info)
{
	CGS_FUNC_ADEV;

	if (NULL == sys_info)
		return -ENODEV;

	if (sizeof(struct cgs_system_info) != sys_info->size)
		return -ENODEV;

	switch (sys_info->info_id) {
	case CGS_SYSTEM_INFO_ADAPTER_BDF_ID:
		sys_info->value = adev->pdev->devfn | (adev->pdev->bus->number << 8);
		break;
	case CGS_SYSTEM_INFO_PCIE_GEN_INFO:
		sys_info->value = adev->pm.pcie_gen_mask;
		break;
	case CGS_SYSTEM_INFO_PCIE_MLW:
		sys_info->value = adev->pm.pcie_mlw_mask;
		break;
	case CGS_SYSTEM_INFO_CG_FLAGS:
		sys_info->value = adev->cg_flags;
		break;
	case CGS_SYSTEM_INFO_PG_FLAGS:
		sys_info->value = adev->pg_flags;
		break;
	default:
		return -ENODEV;
	}

	return 0;
}
