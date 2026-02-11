XGI_SetCRT1FIFO(struct xgi_hw_device_info *HwDeviceExtension,
			    struct vb_device_info *pVBInfo)
{
	unsigned short data;

	data = xgifb_reg_get(pVBInfo->P3c4, 0x3D);
	data &= 0xfe;
	xgifb_reg_set(pVBInfo->P3c4, 0x3D, data);

	xgifb_reg_set(pVBInfo->P3c4, 0x08, 0x34);
	data = xgifb_reg_get(pVBInfo->P3c4, 0x09);
	data &= 0xC0;
	xgifb_reg_set(pVBInfo->P3c4, 0x09, data | 0x30);
	data = xgifb_reg_get(pVBInfo->P3c4, 0x3D);
	data |= 0x01;
	xgifb_reg_set(pVBInfo->P3c4, 0x3D, data);

	if (HwDeviceExtension->jChipType == XG21)
		XGI_SetXG21FPBits(pVBInfo);
}
