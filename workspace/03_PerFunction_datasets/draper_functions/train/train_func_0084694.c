XGI_GetLcdPtr(struct XGI330_LCDDataTablStruct const *table,
		unsigned short ModeIdIndex,
		struct vb_device_info *pVBInfo)
{
	unsigned short i, tempdx, tempbx, modeflag;

	tempbx = 0;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	i = 0;

	while (table[i].PANELID != 0xff) {
		tempdx = pVBInfo->LCDResInfo;
		if (tempbx & 0x0080) {
			tempbx &= (~0x0080);
			tempdx = pVBInfo->LCDTypeInfo;
		}

		if (pVBInfo->LCDInfo & EnableScalingLCD)
			tempdx &= (~PanelResInfo);

		if (table[i].PANELID == tempdx) {
			tempbx = table[i].MASK;
			tempdx = pVBInfo->LCDInfo;

			if (modeflag & HalfDCLK)
				tempdx |= SetLCDLowResolution;

			tempbx &= tempdx;
			if (tempbx == table[i].CAP)
				break;
		}
		i++;
	}

	return table[i].DATAPTR;
}
