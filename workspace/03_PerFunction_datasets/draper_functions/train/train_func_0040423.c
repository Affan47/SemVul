vxge_hw_device_hw_info_get(void __iomem *bar0,
			   struct vxge_hw_device_hw_info *hw_info)
{
	u32 i;
	u64 val64;
	struct vxge_hw_toc_reg __iomem *toc;
	struct vxge_hw_mrpcim_reg __iomem *mrpcim_reg;
	struct vxge_hw_common_reg __iomem *common_reg;
	struct vxge_hw_vpmgmt_reg __iomem *vpmgmt_reg;
	enum vxge_hw_status status;
	struct __vxge_hw_virtualpath vpath;

	memset(hw_info, 0, sizeof(struct vxge_hw_device_hw_info));

	toc = __vxge_hw_device_toc_get(bar0);
	if (toc == NULL) {
		status = VXGE_HW_ERR_CRITICAL;
		goto exit;
	}

	val64 = readq(&toc->toc_common_pointer);
	common_reg = bar0 + val64;

	status = __vxge_hw_device_vpath_reset_in_prog_check(
		(u64 __iomem *)&common_reg->vpath_rst_in_prog);
	if (status != VXGE_HW_OK)
		goto exit;

	hw_info->vpath_mask = readq(&common_reg->vpath_assignments);

	val64 = readq(&common_reg->host_type_assignments);

	hw_info->host_type =
	   (u32)VXGE_HW_HOST_TYPE_ASSIGNMENTS_GET_HOST_TYPE_ASSIGNMENTS(val64);

	for (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) {
		if (!((hw_info->vpath_mask) & vxge_mBIT(i)))
			continue;

		val64 = readq(&toc->toc_vpmgmt_pointer[i]);

		vpmgmt_reg = bar0 + val64;

		hw_info->func_id = __vxge_hw_vpath_func_id_get(vpmgmt_reg);
		if (__vxge_hw_device_access_rights_get(hw_info->host_type,
			hw_info->func_id) &
			VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM) {

			val64 = readq(&toc->toc_mrpcim_pointer);

			mrpcim_reg = bar0 + val64;

			writeq(0, &mrpcim_reg->xgmac_gen_fw_memo_mask);
			wmb();
		}

		val64 = readq(&toc->toc_vpath_pointer[i]);

		spin_lock_init(&vpath.lock);
		vpath.vp_reg = bar0 + val64;
		vpath.vp_open = VXGE_HW_VP_NOT_OPEN;

		status = __vxge_hw_vpath_pci_func_mode_get(&vpath, hw_info);
		if (status != VXGE_HW_OK)
			goto exit;

		status = __vxge_hw_vpath_fw_ver_get(&vpath, hw_info);
		if (status != VXGE_HW_OK)
			goto exit;

		status = __vxge_hw_vpath_card_info_get(&vpath, hw_info);
		if (status != VXGE_HW_OK)
			goto exit;

		break;
	}

	for (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) {
		if (!((hw_info->vpath_mask) & vxge_mBIT(i)))
			continue;

		val64 = readq(&toc->toc_vpath_pointer[i]);
		vpath.vp_reg = bar0 + val64;
		vpath.vp_open = VXGE_HW_VP_NOT_OPEN;

		status =  __vxge_hw_vpath_addr_get(&vpath,
				hw_info->mac_addrs[i],
				hw_info->mac_addr_masks[i]);
		if (status != VXGE_HW_OK)
			goto exit;
	}
exit:
	return status;
}
