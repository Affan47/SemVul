XGI_IsLCDDualLink(struct vb_device_info *pVBInfo)
{

	if ((pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) &&
			(pVBInfo->LCDInfo & SetLCDDualLink))
		return 1;

	return 0;
}
