__vxge_hw_vpath_prc_configure(struct __vxge_hw_device *hldev)
{
	u64 val64;
	struct __vxge_hw_virtualpath *vpath;
	struct vxge_hw_vpath_reg __iomem *vp_reg;

	vxge_trace();

	vpath = &hldev->virtual_path;
	vp_reg = vpath->vp_reg;

	val64 = readq(&vp_reg->prc_cfg1);
	val64 |= VXGE_HW_PRC_CFG1_RTI_TINT_DISABLE;
	writeq(val64, &vp_reg->prc_cfg1);

	val64 = readq(&vpath->vp_reg->prc_cfg6);
	val64 &= ~VXGE_HW_PRC_CFG6_RXD_CRXDT(0x1ff);
	val64 &= ~VXGE_HW_PRC_CFG6_RXD_SPAT(0x1ff);
	val64 |= VXGE_HW_PRC_CFG6_DOORBELL_MODE_EN;
	val64 |= VXGE_HW_PRC_CFG6_RXD_CRXDT(0x3);
	val64 |= VXGE_HW_PRC_CFG6_RXD_SPAT(0xf);
	writeq(val64, &vpath->vp_reg->prc_cfg6);

	writeq(VXGE_HW_PRC_CFG5_RXD0_ADD(
			(u64)virt_to_bus(vpath->ringh.rxdl) >> 3),
			&vp_reg->prc_cfg5);

	val64 = readq(&vp_reg->prc_cfg4);
	val64 |= VXGE_HW_PRC_CFG4_IN_SVC;
	val64 &= ~VXGE_HW_PRC_CFG4_RING_MODE(0x3);
	val64 |= VXGE_HW_PRC_CFG4_RING_MODE(
			VXGE_HW_PRC_CFG4_RING_MODE_ONE_BUFFER);
	val64 |= VXGE_HW_PRC_CFG4_RTH_DISABLE;

	writeq(val64, &vp_reg->prc_cfg4);
	return;
}
