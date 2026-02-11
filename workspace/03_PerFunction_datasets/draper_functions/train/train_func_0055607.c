vxge_hw_flash_fw(struct __vxge_hw_device *hldev)
{
	u64 data0 = 0, data1 = 0, steer_ctrl = 0;
	struct __vxge_hw_virtualpath *vpath;
	enum vxge_hw_status status;
	u32 ret;

	vpath = &hldev->virtual_paths[hldev->first_vp_id];

	status = vxge_hw_vpath_fw_api(vpath,
				      VXGE_HW_FW_UPGRADE_ACTION,
				      VXGE_HW_FW_UPGRADE_MEMO,
				      VXGE_HW_FW_UPGRADE_OFFSET_COMMIT,
				      &data0, &data1, &steer_ctrl);
	if (status != VXGE_HW_OK) {
		vxge_debug_init(VXGE_ERR, "%s: FW upgrade failed", __func__);
		goto exit;
	}

	ret = VXGE_HW_RTS_ACCESS_STEER_CTRL_GET_ACTION(steer_ctrl) & 0x7F;
	if (ret != 1) {
		vxge_debug_init(VXGE_ERR, "%s: FW commit failed with error %d",
				__func__, ret);
		status = VXGE_HW_FAIL;
	}

exit:
	return status;
}
