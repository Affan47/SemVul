vxge_hw_set_fw_api(struct __vxge_hw_device *hldev,
		u64 vp_id,
		u32 action,
		u32 offset,
		u64 data0,
		u64 data1)
{
	enum vxge_hw_status status = VXGE_HW_OK;
	u64 val64;
	u32 fw_memo = VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO;

	struct vxge_hw_vpath_reg __iomem *vp_reg;

	vp_reg = (struct vxge_hw_vpath_reg __iomem *)hldev->vpath_reg[vp_id];

	writeq(data0, &vp_reg->rts_access_steer_data0);
	writeq(data1, &vp_reg->rts_access_steer_data1);

	wmb();

	val64 = VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION(action) |
		VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL(fw_memo) |
		VXGE_HW_RTS_ACCESS_STEER_CTRL_OFFSET(offset) |
		VXGE_HW_RTS_ACCESS_STEER_CTRL_STROBE;

	writeq(val64, &vp_reg->rts_access_steer_ctrl);

	wmb();

	status = __vxge_hw_device_register_poll(
			&vp_reg->rts_access_steer_ctrl,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_STROBE,
			WAIT_FACTOR *
			VXGE_HW_DEF_DEVICE_POLL_MILLIS);

	if (status != VXGE_HW_OK)
		return VXGE_HW_FAIL;

	val64 = readq(&vp_reg->rts_access_steer_ctrl);

	if (val64 & VXGE_HW_RTS_ACCESS_STEER_CTRL_RMACJ_STATUS)
		status = VXGE_HW_OK;
	else
		status = VXGE_HW_FAIL;

	return status;
}
