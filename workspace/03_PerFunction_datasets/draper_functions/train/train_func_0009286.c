XGI_DisplayOff(struct xgifb_video_info *xgifb_info,
		struct xgi_hw_device_info *pXGIHWDE,
		struct vb_device_info *pVBInfo)
{

	if (pXGIHWDE->jChipType == XG21) {
		if (pVBInfo->IF_DEF_LVDS == 1) {

			XGI_XG21BLSignalVDD(0x02, 0x00, pVBInfo);
			mdelay(xgifb_info->lvds_data.PSC_S3);
		} else {

			XGI_XG21BLSignalVDD(0x20, 0x00, pVBInfo);
		}
	}

	if (pXGIHWDE->jChipType == XG27) {
		if ((XGI_XG27GetPSCValue(pVBInfo) & 0x2)) {

			XGI_XG27BLSignalVDD(0x02, 0x00, pVBInfo);
			mdelay(xgifb_info->lvds_data.PSC_S3);
		}

		if (pVBInfo->IF_DEF_LVDS == 0)

			XGI_XG27BLSignalVDD(0x20, 0x00, pVBInfo);
	}

	xgifb_reg_and_or(pVBInfo->P3c4, 0x01, 0xDF, 0x20);
}
