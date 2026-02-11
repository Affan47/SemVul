XGI_GetLVDSData(unsigned short ModeIdIndex,
			    struct vb_device_info *pVBInfo)
{
	struct SiS_LVDSData const *LCDPtr;

	if (!(pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)))
		return;

	LCDPtr = XGI_GetLcdPtr(XGI_EPLLCDDataPtr, ModeIdIndex, pVBInfo);
	pVBInfo->VGAHT	= LCDPtr->VGAHT;
	pVBInfo->VGAVT	= LCDPtr->VGAVT;
	pVBInfo->HT	= LCDPtr->LCDHT;
	pVBInfo->VT	= LCDPtr->LCDVT;

	if (pVBInfo->LCDInfo & (SetLCDtoNonExpanding | EnableScalingLCD))
		return;

	if ((pVBInfo->LCDResInfo == Panel_1024x768) ||
	    (pVBInfo->LCDResInfo == Panel_1024x768x75)) {
		pVBInfo->HDE = 1024;
		pVBInfo->VDE = 768;
	} else if ((pVBInfo->LCDResInfo == Panel_1280x1024) ||
		   (pVBInfo->LCDResInfo == Panel_1280x1024x75)) {
		pVBInfo->HDE = 1280;
		pVBInfo->VDE = 1024;
	} else if (pVBInfo->LCDResInfo == Panel_1400x1050) {
		pVBInfo->HDE = 1400;
		pVBInfo->VDE = 1050;
	} else {
		pVBInfo->HDE = 1600;
		pVBInfo->VDE = 1200;
	}
}
