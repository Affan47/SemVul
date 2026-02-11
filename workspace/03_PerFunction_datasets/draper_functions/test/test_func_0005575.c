XGI_SetLCDCap_B(unsigned short tempcx,
			    struct vb_device_info *pVBInfo)
{
	if (tempcx & EnableLCD24bpp)
		xgifb_reg_and_or(pVBInfo->Part2Port, 0x1A, 0xE0,
				(unsigned short) (((tempcx & 0x00ff) >> 6)
						| 0x0c));
	else
		xgifb_reg_and_or(pVBInfo->Part2Port, 0x1A, 0xE0,
				(unsigned short) (((tempcx & 0x00ff) >> 6)
						| 0x18));
}
