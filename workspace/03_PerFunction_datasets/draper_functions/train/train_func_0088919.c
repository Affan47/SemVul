atombios_crtc_set_timing(struct drm_crtc *crtc,
				     struct drm_display_mode *mode)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	SET_CRTC_TIMING_PARAMETERS_PS_ALLOCATION args;
	int index = GetIndexIntoMasterTable(COMMAND, SetCRTC_Timing);
	u16 misc = 0;

	memset(&args, 0, sizeof(args));
	args.usH_Total = cpu_to_le16(mode->crtc_htotal);
	args.usH_Disp = cpu_to_le16(mode->crtc_hdisplay);
	args.usH_SyncStart = cpu_to_le16(mode->crtc_hsync_start);
	args.usH_SyncWidth =
		cpu_to_le16(mode->crtc_hsync_end - mode->crtc_hsync_start);
	args.usV_Total = cpu_to_le16(mode->crtc_vtotal);
	args.usV_Disp = cpu_to_le16(mode->crtc_vdisplay);
	args.usV_SyncStart = cpu_to_le16(mode->crtc_vsync_start);
	args.usV_SyncWidth =
		cpu_to_le16(mode->crtc_vsync_end - mode->crtc_vsync_start);

	args.ucOverscanRight = radeon_crtc->h_border;
	args.ucOverscanLeft = radeon_crtc->h_border;
	args.ucOverscanBottom = radeon_crtc->v_border;
	args.ucOverscanTop = radeon_crtc->v_border;

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		misc |= ATOM_VSYNC_POLARITY;
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		misc |= ATOM_HSYNC_POLARITY;
	if (mode->flags & DRM_MODE_FLAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		misc |= ATOM_INTERLACE;
	if (mode->flags & DRM_MODE_FLAG_DBLCLK)
		misc |= ATOM_DOUBLE_CLOCK_MODE;
	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		misc |= ATOM_H_REPLICATIONBY2 | ATOM_V_REPLICATIONBY2;

	args.susModeMiscInfo.usAccess = cpu_to_le16(misc);
	args.ucCRTC = radeon_crtc->crtc_id;

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}
