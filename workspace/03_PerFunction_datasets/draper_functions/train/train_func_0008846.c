run_lvds_table(struct drm_device *dev, struct dcb_output *dcbent, int head, enum LVDS_script script, int pxclk)
{


	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvbios *bios = &drm->vbios;
	unsigned int outputset = (dcbent->or == 4) ? 1 : 0;
	uint16_t scriptptr = 0, clktable;


	switch (script) {
	case LVDS_INIT:
		return -ENOSYS;
	case LVDS_BACKLIGHT_ON:
	case LVDS_PANEL_ON:
		scriptptr = ROM16(bios->data[bios->fp.lvdsmanufacturerpointer + 7 + outputset * 2]);
		break;
	case LVDS_BACKLIGHT_OFF:
	case LVDS_PANEL_OFF:
		scriptptr = ROM16(bios->data[bios->fp.lvdsmanufacturerpointer + 11 + outputset * 2]);
		break;
	case LVDS_RESET:
		clktable = bios->fp.lvdsmanufacturerpointer + 15;
		if (dcbent->or == 4)
			clktable += 8;

		if (dcbent->lvdsconf.use_straps_for_mode) {
			if (bios->fp.dual_link)
				clktable += 4;
			if (bios->fp.if_is_24bit)
				clktable += 2;
		} else {

			int cmpval_24bit = (dcbent->or == 4) ? 4 : 1;

			if (bios->fp.dual_link) {
				clktable += 4;
				cmpval_24bit <<= 1;
			}

			if (bios->fp.strapless_is_24bit & cmpval_24bit)
				clktable += 2;
		}

		clktable = ROM16(bios->data[clktable]);
		if (!clktable) {
			NV_ERROR(drm, "Pixel clock comparison table not found\n");
			return -ENOENT;
		}
		scriptptr = clkcmptable(bios, clktable, pxclk);
	}

	if (!scriptptr) {
		NV_ERROR(drm, "LVDS output init script not found\n");
		return -ENOENT;
	}
	run_digital_op_script(dev, scriptptr, dcbent, head, bios->fp.dual_link);

	return 0;
}
