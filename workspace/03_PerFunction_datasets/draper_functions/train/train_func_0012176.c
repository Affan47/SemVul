__vxge_hw_vpath_swapper_set(struct vxge_hw_vpath_reg __iomem *vpath_reg)
{
	vxge_trace();

#if (__BYTE_ORDER != __BIG_ENDIAN)
	u64 val64;

	val64 = readq(&vpath_reg->vpath_general_cfg1);
	wmb();
	val64 |= VXGE_HW_VPATH_GENERAL_CFG1_CTL_BYTE_SWAPEN;
	writeq(val64, &vpath_reg->vpath_general_cfg1);
	wmb();
#endif
	return VXGE_HW_OK;
}
