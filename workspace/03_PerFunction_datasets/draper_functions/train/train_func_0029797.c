vxge_hw_vpath_vid_delete(struct __vxge_hw_vpath_handle *vp, u64 vid)
{
	enum vxge_hw_status status = VXGE_HW_OK;

	if (vp == NULL) {
		status = VXGE_HW_ERR_INVALID_HANDLE;
		goto exit;
	}

	status = __vxge_hw_vpath_rts_table_set(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_DELETE_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_VID,
			0, VXGE_HW_RTS_ACCESS_STEER_DATA0_VLAN_ID(vid), 0);
exit:
	return status;
}
