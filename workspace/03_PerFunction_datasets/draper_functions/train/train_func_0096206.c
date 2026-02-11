XGI_SetVCLKState(struct xgi_hw_device_info *HwDeviceExtension,
		unsigned short RefreshRateTableIndex,
		struct vb_device_info *pVBInfo)
{
	unsigned short data, data2 = 0;
	short VCLK;

	unsigned char index;

	index = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRTVCLK;
	index &= IndexMask;
	VCLK = XGI_VCLKData[index].CLOCK;

	data = xgifb_reg_get(pVBInfo->P3c4, 0x32);
	data &= 0xf3;
	if (VCLK >= 200)
		data |= 0x0c;

	if (HwDeviceExtension->jChipType >= XG20)
		data &= ~0x04;

	xgifb_reg_set(pVBInfo->P3c4, 0x32, data);

	if (HwDeviceExtension->jChipType < XG20) {
		data = xgifb_reg_get(pVBInfo->P3c4, 0x1F);
		data &= 0xE7;
		if (VCLK < 200)
			data |= 0x10;
		xgifb_reg_set(pVBInfo->P3c4, 0x1F, data);
	}

	data2 = 0x00;

	xgifb_reg_and_or(pVBInfo->P3c4, 0x07, 0xFC, data2);
	if (HwDeviceExtension->jChipType >= XG27)
		xgifb_reg_and_or(pVBInfo->P3c4, 0x40, 0xFC, data2 & 0x03);

}
