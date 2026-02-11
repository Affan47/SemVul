XGIfb_detect_VB(struct xgifb_video_info *xgifb_info)
{
	u8 cr32, temp = 0;

	xgifb_info->TV_plug = xgifb_info->TV_type = 0;

	cr32 = xgifb_reg_get(XGICR, IND_XGI_SCRATCH_REG_CR32);

	if ((cr32 & SIS_CRT1) && !XGIfb_crt1off)
		XGIfb_crt1off = 0;
	else {
		if (cr32 & 0x5F)
			XGIfb_crt1off = 1;
		else
			XGIfb_crt1off = 0;
	}

	if (!xgifb_info->display2_force) {
		if (cr32 & SIS_VB_TV)
			xgifb_info->display2 = XGIFB_DISP_TV;
		else if (cr32 & SIS_VB_LCD)
			xgifb_info->display2 = XGIFB_DISP_LCD;
		else if (cr32 & SIS_VB_CRT2)
			xgifb_info->display2 = XGIFB_DISP_CRT;
		else
			xgifb_info->display2 = XGIFB_DISP_NONE;
	}

	if (XGIfb_tvplug != -1)

		xgifb_info->TV_plug = XGIfb_tvplug;
	else if (cr32 & SIS_VB_HIVISION) {
		xgifb_info->TV_type = TVMODE_HIVISION;
		xgifb_info->TV_plug = TVPLUG_SVIDEO;
	} else if (cr32 & SIS_VB_SVIDEO)
		xgifb_info->TV_plug = TVPLUG_SVIDEO;
	else if (cr32 & SIS_VB_COMPOSITE)
		xgifb_info->TV_plug = TVPLUG_COMPOSITE;
	else if (cr32 & SIS_VB_SCART)
		xgifb_info->TV_plug = TVPLUG_SCART;

	if (xgifb_info->TV_type == 0) {
		temp = xgifb_reg_get(XGICR, 0x38);
		if (temp & 0x10)
			xgifb_info->TV_type = TVMODE_PAL;
		else
			xgifb_info->TV_type = TVMODE_NTSC;
	}


	if (XGIfb_forcecrt1 != -1) {
		if (XGIfb_forcecrt1)
			XGIfb_crt1off = 0;
		else
			XGIfb_crt1off = 1;
	}
}
