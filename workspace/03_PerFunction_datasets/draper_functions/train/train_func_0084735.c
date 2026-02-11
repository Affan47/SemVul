vxge_hw_device_getpause_data(struct __vxge_hw_device *hldev,
						 u32 port, u32 *tx, u32 *rx)
{
	u64 val64;
	enum vxge_hw_status status = VXGE_HW_OK;

	if ((hldev == NULL) || (hldev->magic != VXGE_HW_DEVICE_MAGIC)) {
		status = VXGE_HW_ERR_INVALID_DEVICE;
		goto exit;
	}

	if (port > VXGE_HW_MAC_MAX_MAC_PORT_ID) {
		status = VXGE_HW_ERR_INVALID_PORT;
		goto exit;
	}

	if (!(hldev->access_rights & VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM)) {
		status = VXGE_HW_ERR_PRIVILAGED_OPEARATION;
		goto exit;
	}

	val64 = readq(&hldev->mrpcim_reg->rxmac_pause_cfg_port[port]);
	if (val64 & VXGE_HW_RXMAC_PAUSE_CFG_PORT_GEN_EN)
		*tx = 1;
	if (val64 & VXGE_HW_RXMAC_PAUSE_CFG_PORT_RCV_EN)
		*rx = 1;
exit:
	return status;
}
