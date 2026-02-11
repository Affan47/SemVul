__vxge_hw_vpath_initialize(struct __vxge_hw_device *hldev, u32 vp_id)
{
	u64 val64;
	u32 val32;
	enum vxge_hw_status status = VXGE_HW_OK;
	struct __vxge_hw_virtualpath *vpath;
	struct vxge_hw_vpath_reg __iomem *vp_reg;

	vpath = &hldev->virtual_paths[vp_id];

	if (!(hldev->vpath_assignments & vxge_mBIT(vp_id))) {
		status = VXGE_HW_ERR_VPATH_NOT_AVAILABLE;
		goto exit;
	}
	vp_reg = vpath->vp_reg;

	status =  __vxge_hw_vpath_swapper_set(vpath->vp_reg);
	if (status != VXGE_HW_OK)
		goto exit;

	status =  __vxge_hw_vpath_mac_configure(hldev, vp_id);
	if (status != VXGE_HW_OK)
		goto exit;

	status =  __vxge_hw_vpath_kdfc_configure(hldev, vp_id);
	if (status != VXGE_HW_OK)
		goto exit;

	status = __vxge_hw_vpath_tim_configure(hldev, vp_id);
	if (status != VXGE_HW_OK)
		goto exit;

	val64 = readq(&vp_reg->rtdma_rd_optimization_ctrl);


	status  = __vxge_hw_vpath_pci_read(vpath, 1, 0x78, &val32);
	if (status == VXGE_HW_OK) {
		val32 = (val32 & VXGE_HW_PCI_EXP_DEVCTL_READRQ) >> 12;
		val64 &=
		    ~(VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_FILL_THRESH(7));
		val64 |=
		    VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_FILL_THRESH(val32);

		val64 |= VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_WAIT_FOR_SPACE;
	}

	val64 &= ~(VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_ADDR_BDRY(7));
	val64 |=
	    VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_ADDR_BDRY(
		    VXGE_HW_MAX_PAYLOAD_SIZE_512);

	val64 |= VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_ADDR_BDRY_EN;
	writeq(val64, &vp_reg->rtdma_rd_optimization_ctrl);

exit:
	return status;
}
