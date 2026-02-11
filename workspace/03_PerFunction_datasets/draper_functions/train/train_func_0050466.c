vxge_hw_vpath_mac_addr_delete(
	struct __vxge_hw_vpath_handle *vp,
	u8 (macaddr)[ETH_ALEN],
	u8 (macaddr_mask)[ETH_ALEN])
{
	u32 i;
	u64 data1 = 0ULL;
	u64 data2 = 0ULL;
	enum vxge_hw_status status = VXGE_HW_OK;

	if (vp == NULL) {
		status = VXGE_HW_ERR_INVALID_HANDLE;
		goto exit;
	}

	for (i = 0; i < ETH_ALEN; i++) {
		data1 <<= 8;
		data1 |= (u8)macaddr[i];

		data2 <<= 8;
		data2 |= (u8)macaddr_mask[i];
	}

	status = __vxge_hw_vpath_rts_table_set(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_DELETE_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA,
			0,
			VXGE_HW_RTS_ACCESS_STEER_DATA0_DA_MAC_ADDR(data1),
			VXGE_HW_RTS_ACCESS_STEER_DATA1_DA_MAC_ADDR_MASK(data2));
exit:
	return status;
}
