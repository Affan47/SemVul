nv04_dfp_bind_head(struct drm_device *dev, struct dcb_output *dcbent,
			int head, bool dl)
{


	int ramdac = (dcbent->or & DCB_OUTPUT_C) >> 2;
	uint8_t tmds04 = 0x80;

	if (head != ramdac)
		tmds04 = 0x88;

	if (dcbent->type == DCB_OUTPUT_LVDS)
		tmds04 |= 0x01;

	nv_write_tmds(dev, dcbent->or, 0, 0x04, tmds04);

	if (dl)
		nv_write_tmds(dev, dcbent->or, 1, 0x04, tmds04 ^ 0x08);
}
